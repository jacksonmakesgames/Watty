import os
import sys
from itertools import islice
import subprocess
from textwrap import dedent
from threading import Thread
import platform
import math
import http
import http.server
import socket
import webbrowser
import time

try:
    from tkinter import * # Python 3
    from tkinter import messagebox
    from queue import Queue, Empty # Python 3
except ImportError:
    print("Must use python 3+")
    quit()

dir_path = os.path.dirname(os.path.realpath(__file__))

LOG_WIDTH = 170

def open_file(path):
    if platform.system() == "Windows":
        os.startfile(path)
    elif platform.system() == "Darwin":
        subprocess.Popen(["open", path])
    else:
        subprocess.Popen(["xdg-open", path])


class LogBox(Listbox):
  foreground_colors = {
      'bright' : {'30' : 'Black', '31' : 'Red', '32' : 'Green', '33' : 'Brown', '34' : 'Blue', '35' : 'Purple', '36' : 'Cyan', '37' : 'White'},}
 
  color_pat = re.compile('\x01?\x1b\[([\d+;]*?)m\x02?')
  inner_color_pat = re.compile("^(\d+;?)+$")
 
  def __init__(self, parent):
    """
    initialize our specialized tkinter Text widget
    """
    Listbox.__init__(self, parent, height=20, width=LOG_WIDTH)
    self.listbox_log = self
    self.font=(None, 10)
    self.known_tags = set([])
    # register a default color tag
    self.register_tag("30", "Black", "White")
    self.reset_to_default_attribs()
     
    self.scrollbar_log = Scrollbar(parent) 
    self.scrollbar_log.grid(row=0, column = 11,sticky=N+S)
    self.listbox_log.configure(yscrollcommand = self.scrollbar_log.set)
    self.scrollbar_log.configure(command = self.listbox_log.yview)
 
  def reset_to_default_attribs(self):
    self.tag = '30'
    self.bright = 'bright'
    self.foregroundcolor = 'Black'
    self.backgroundcolor = 'White'
 
  def register_tag(self, txt, foreground, background):
    """
    register a tag with name txt and with given
    foreground and background color
    """
    # self.tag_config(txt, foreground=foreground, background=background)
    self.known_tags.add(txt)
     
  def write(self, text, is_editable=False):
    """
    add text to the text widget
    """
    # first split the text at color codes, stripping stuff like the <ESC> 
    # and \[ characters and keeping only the inner "0;23"-like codes
    arr = re.findall(r'\\x1b\[[0-9;]+m', text)
    if(len(arr)>0):
        self.tag= re.findall(r"[0-9]+", arr[0])[1]
    else:
        self.tag = '30' #default
    ansi = re.compile(r'\\x1b\[[0-9;]+m')
    result = ansi.sub('', str(text))

    string = "$ "
    for c in (result):
        string+=c
        if(len(string)>LOG_WIDTH):
            self.insert(END,string)
            self.itemconfig(self.size()-1,{'fg': self.foreground_colors['bright'][self.tag]})
            string ="     "

    self.insert(END, string)
    self.itemconfig(self.size()-1,{'fg': self.foreground_colors['bright'][self.tag]})

    self.listbox_log.select_clear(self.listbox_log.size() - 2)     #Clear the current selected item     
    self.listbox_log.select_set(END)                             #Select the new item
    self.listbox_log.yview(END)                                  #Set the scrollbar to the end of the listbox
    self.listbox_log.selection_clear(0, END)

def iter_except(function, exception):
    """Works like builtin 2-argument `iter()`, but stops on `exception`."""
    try:
        while True:
            yield function()
    except exception:
        return

class WattyTools:

    def __init__(self, root):
        self.root = root
        self.root.title("{Watty Tools}")
        self.root.geometry("1200x600")
        self.process = None
        self.web_process = None
        self.running_web_service = False
        self.webThread = None
        self.port = 8080

    def run_build(self, mode, configuration):
        if(self.process is not None):
            self.process.kill()

        if platform.system() == "Windows":
            if mode.endswith("web"):
                mode = "\\"+mode+".bat"
            else:
                mode = "\\"+mode+"_"+configuration.lower() + ".bat"
        
        self.process = subprocess.Popen(["cmd", "/c", "start", "/MIN", "/w","/B", dir_path+mode], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
        q = Queue(maxsize=1024)  # limit output buffering (may stall subprocess)
        q.put("")
        q.put("Starting build: " + mode)

        t = Thread(target=self.reader_thread, args=[q])
        t.daemon = True # close pipe if GUI process exits
        t.start()

        # show subprocess' stdout in GUI
        self.update(q) # start update loop
        return

    def run_web_server(self):
        try:
            if(self.web_process is not None):
                self.web_process.kill()
                self.listbox.write("Closed running web server")
            try:
                web_dir = os.path.normpath(os.path.dirname(__file__) + os.sep + os.pardir)
                os.chdir(web_dir)
                self.listbox.write("Serving " + web_dir)
                self.web_process = subprocess.Popen(["cmd", "/c", "start", "/MIN", "/w","/B", ".\\dependencies\\emscripten\\upstream\\emscripten\\emrun.bat", "--serve_after_close", "--kill_start", "."],stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
                self.listbox.write("web_process PID: " + str(self.web_process.pid))
            except Exception as e:
                self.listbox.write(str(e))
        except Exception as ex:
                self.listbox.write("Error on web thread:" + str(ex))
        #finally:
        #        self.listbox.write("Ended web thread")

      

    def run_program_windows(self, program, config):
        q = Queue(maxsize=1024)  # limit output buffering (may stall subprocess)
        q.put("")
        q.put("Starting program: " + program)
        self.process = subprocess.Popen([dir_path+"\\..\\bin\\"+config+"\\"+program],stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
        t = Thread(target=self.reader_thread, args=[q])
        t.daemon = True # close pipe if GUI process exits
        t.start()

        # show subprocess' stdout in GUI
        self.update(q) # start update loop
        return

    def run_demos(self, mode, config):
        if mode == 'Windows':
            open_file(os.path.normpath(os.path.dirname(__file__) + os.sep + os.pardir) + os.path.dirname("/Demos/bin/" + config + "/"))
        elif mode == 'Web':
            self.run_watty(mode, config)
        return

    def run_watty(self, mode, config):
        if mode == 'Windows':
            t = Thread(target=self.run_program_windows, args=["Sandbox.exe", config])
            t.daemon = True # close pipe if GUI process exits
            t.start()
        elif mode == 'Web':
            self.run_web_server()
            return
            if(self.webThread is not None):
                self.webThread.join(2)
            self.webThread = Thread(target=self.run_web_server)
            self.webThread.daemon = True # close pipe if GUI process exits
            self.webThread.start()

    def reader_thread(self, q):
        """Read subprocess output and put it into the queue."""
        try:
            with self.process.stdout as pipe:
                for line in iter(pipe.readline, b''):
                    q.put(line)
        finally:
            q.put(None)

    def update(self, q):
        """Update GUI with items from the queue."""
        for line in iter_except(q.get_nowait, Empty): # display all content
            if line is None:
                self.process.kill()
                self.process = None
                return

            else:
                result = str(line).replace('\\r', '\r').replace('\\\\', '\\').replace("b'","").replace("b\"","").replace("\\n'", "\n")
                self.listbox.write(result)
                break # display no more than one line per 40 milliseconds
          

        self.root.after(40, self.update, q) # schedule next update

    def quit(self):
        if(self.process is not None): 
            self.process.kill() # exit subprocess if GUI is closed
        if self.web_process is not None:
            self.web_process.kill() 
        self.root.destroy()




root = Tk()
root.iconbitmap(dir_path+"/../favicon.ico")

app = WattyTools(root)
root.protocol("WM_DELETE_WINDOW", app.quit)

listFrame = Frame(root)
listFrame.grid(row=0, column=0, columnspan=2, padx=20, pady=20, sticky=N+E+W+S)
listFrame.grid_columnconfigure(1, weight=1)

app.listbox = LogBox(listFrame)
app.listbox.grid(row=0, column=0, sticky=W+E+N+S)

wattyFrame = Frame(root, borderwidth=2, relief="sunken")
wattyFrame.grid(row = 2, column = 0, columnspan=2, padx=20, pady=10, sticky=W)
wattyLabel = Label(wattyFrame, text="Watty Game Engine")
wattyLabel.grid(row = 0, column = 0, padx=5, pady=5)

watty_plat = StringVar(root)
choicesP = { 'Windows','Web'}
watty_plat.set('Windows') # set the default option

configuration = StringVar(root)
choicesC = { 'Debug','Release'}
configuration.set('Debug') # set the default option

popupMenuWP = OptionMenu(wattyFrame, watty_plat, *choicesP)
Label(wattyFrame, text="Platform:").grid(row = 1, column = 0, sticky=N+E+W+S)
popupMenuWP.grid(row = 2, column =0, sticky=N+E+W+S)

popupMenuWC = OptionMenu(wattyFrame, configuration, *choicesC)
wattyConfigLabel = Label(wattyFrame, text="Config:")
wattyConfigLabel.grid(row = 1, column = 1, sticky=N+E+W+S)
popupMenuWC.grid(row = 2, column =1, sticky=N+E+W+S)

b = Button(wattyFrame, text="Build", command=lambda: app.run_build("build_watty_"+watty_plat.get().lower(), configuration.get()))
b.grid(row = 3, column =0, padx=5, pady=5, sticky=N+E+S+W)

b = Button(wattyFrame, text="Clean", command=lambda: app.run_build("clean_watty_"+watty_plat.get().lower(), configuration.get()))
b.grid(row = 3, column =1, padx=5, pady=5, sticky=N+E+S+W)

b = Button(wattyFrame, text="Run", command=lambda: app.run_watty(watty_plat.get(), configuration.get()))
b.grid(row = 4, column =0, padx=5, pady=5, sticky=N+E+S+W)




                #######
                #DEMOS#
                #######


demosFrame = Frame(root, borderwidth=2, relief="sunken")
demosFrame.grid(row = 2, column =1, columnspan=2, padx=5, pady=5, stick=W)
demosLabel = Label(demosFrame, text="Demos:")
demosLabel.grid(row = 0, column =0, padx=5, pady=5)


demos_plat = StringVar(root)
choicesPD = { 'Windows','Web'}
demos_plat.set('Windows') # set the default option

configurationD = StringVar(root)
choicesCD = { 'Debug','Release'}
configurationD.set('Debug') # set the default option

popupMenuDP = OptionMenu(demosFrame, demos_plat, *choicesPD)
Label(demosFrame, text="Platform:").grid(row = 1, column = 0, sticky=N+E+W+S)
popupMenuDP.grid(row = 2, column =0, sticky=N+E+W+S)

popupMenuDC = OptionMenu(demosFrame, configurationD, *choicesCD)
demosConfigLabel = Label(demosFrame, text="Config:")
demosConfigLabel.grid(row = 1, column = 1, sticky=N+E+W+S)
popupMenuDC.grid(row = 2, column =1, sticky=N+E+W+S)

b = Button(demosFrame, text="Build", command=lambda: app.run_build("build_demos_"+demos_plat.get().lower(), configurationD.get()))
b.grid(row = 3, column =0, padx=5, pady=5, sticky=N+E+S+W)

b = Button(demosFrame, text="Clean", command=lambda: app.run_build("clean_demos_"+demos_plat.get().lower(), configurationD.get()))
b.grid(row = 3, column =1, padx=5, pady=5, sticky=N+E+S+W)

b = Button(demosFrame, text="Run", command=lambda: app.run_demos(demos_plat.get(), configurationD.get()))
b.grid(row = 4, column =0, padx=5, pady=5, sticky=N+E+S+W)



def change_watty_platform(*args):
        if watty_plat.get() == "Web":
            popupMenuWC.grid_forget()
            wattyConfigLabel.grid_forget()
        else:
            wattyConfigLabel.grid(row = 1, column = 1)
            popupMenuWC.grid(row = 2, column =1)
  
def change_demos_platform(*args):
        if demos_plat.get() == "Web":
            popupMenuDC.grid_forget()
            demosConfigLabel.grid_forget()
        else:
            demosConfigLabel.grid(row = 1, column = 1)
            popupMenuDC.grid(row = 2, column =1)
 
watty_plat.trace('w', change_watty_platform)
demos_plat.trace('w', change_demos_platform)

root.mainloop()