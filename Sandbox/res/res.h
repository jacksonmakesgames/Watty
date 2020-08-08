#pragma once
//AUTO-GENERATED FILE, EDIT AT YOUR OWN RISK

#include <Resource.h>
struct RawResources {
	//AUTO-BEGIN-RES
	//
static const unsigned char audio_drums_wav[];;
static const unsigned audio_drums_wav_size;
;
static const unsigned char audio_sci_fi_ogg[];;
static const unsigned audio_sci_fi_ogg_size;
;
static const unsigned char fonts_Lobster_LICENSE_txt[];;
static const unsigned fonts_Lobster_LICENSE_txt_size;
;
static const unsigned char fonts_Lobster_ttf[];;
static const unsigned fonts_Lobster_ttf_size;
;
static const unsigned char fonts_LuckiestGuy_LICENSE_txt[];;
static const unsigned fonts_LuckiestGuy_LICENSE_txt_size;
;
static const unsigned char fonts_LuckiestGuy_ttf[];;
static const unsigned fonts_LuckiestGuy_ttf_size;
;
static const unsigned char fonts_Roboto_Bold_ttf[];;
static const unsigned fonts_Roboto_Bold_ttf_size;
;
static const unsigned char fonts_Roboto_BoldItalic_ttf[];;
static const unsigned fonts_Roboto_BoldItalic_ttf_size;
;
static const unsigned char fonts_Roboto_Italic_ttf[];;
static const unsigned fonts_Roboto_Italic_ttf_size;
;
static const unsigned char fonts_Roboto_Light_ttf[];;
static const unsigned fonts_Roboto_Light_ttf_size;
;
static const unsigned char fonts_Roboto_Regular_ttf[];;
static const unsigned fonts_Roboto_Regular_ttf_size;
;
static const unsigned char fonts_consola_ttf[];;
static const unsigned fonts_consola_ttf_size;
;
static const unsigned char shaders_basic_vert[];;
static const unsigned shaders_basic_vert_size;
;
static const unsigned char shaders_basic_lit_frag[];;
static const unsigned shaders_basic_lit_frag_size;
;
static const unsigned char shaders_basic_unlit_frag[];;
static const unsigned shaders_basic_unlit_frag_size;
;
static const unsigned char test_test_png[];;
static const unsigned test_test_png_size;
;
static const unsigned char textures_asterisk_png[];;
static const unsigned textures_asterisk_png_size;
;
static const unsigned char textures_smoke_png[];;
static const unsigned textures_smoke_png_size;
;
static const unsigned char textures_test_png[];;
static const unsigned textures_test_png_size;

	//AUTO-END-RES
static void Init() {
	//AUTO-BEGIN-INIT
	//
Resources::all.push_back(new Resource("audio/drums.wav", audio_drums_wav, audio_drums_wav_size));
;
Resources::all.push_back(new Resource("audio/sci_fi.ogg", audio_sci_fi_ogg, audio_sci_fi_ogg_size));
;
Resources::all.push_back(new Resource("fonts/Lobster-LICENSE.txt", fonts_Lobster_LICENSE_txt, fonts_Lobster_LICENSE_txt_size));
;
Resources::all.push_back(new Resource("fonts/Lobster.ttf", fonts_Lobster_ttf, fonts_Lobster_ttf_size));
;
Resources::all.push_back(new Resource("fonts/LuckiestGuy-LICENSE.txt", fonts_LuckiestGuy_LICENSE_txt, fonts_LuckiestGuy_LICENSE_txt_size));
;
Resources::all.push_back(new Resource("fonts/LuckiestGuy.ttf", fonts_LuckiestGuy_ttf, fonts_LuckiestGuy_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto-Bold.ttf", fonts_Roboto_Bold_ttf, fonts_Roboto_Bold_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto-BoldItalic.ttf", fonts_Roboto_BoldItalic_ttf, fonts_Roboto_BoldItalic_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto-Italic.ttf", fonts_Roboto_Italic_ttf, fonts_Roboto_Italic_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto-Light.ttf", fonts_Roboto_Light_ttf, fonts_Roboto_Light_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto-Regular.ttf", fonts_Roboto_Regular_ttf, fonts_Roboto_Regular_ttf_size));
;
Resources::all.push_back(new Resource("fonts/consola.ttf", fonts_consola_ttf, fonts_consola_ttf_size));
;
Resources::all.push_back(new Resource("shaders/basic.vert", shaders_basic_vert, shaders_basic_vert_size));
;
Resources::all.push_back(new Resource("shaders/basic_lit.frag", shaders_basic_lit_frag, shaders_basic_lit_frag_size));
;
Resources::all.push_back(new Resource("shaders/basic_unlit.frag", shaders_basic_unlit_frag, shaders_basic_unlit_frag_size));
;
Resources::all.push_back(new Resource("test/test.png", test_test_png, test_test_png_size));
;
Resources::all.push_back(new Resource("textures/asterisk.png", textures_asterisk_png, textures_asterisk_png_size));
;
Resources::all.push_back(new Resource("textures/smoke.png", textures_smoke_png, textures_smoke_png_size));
;
Resources::all.push_back(new Resource("textures/test.png", textures_test_png, textures_test_png_size));

	//AUTO-END-INIT
}
};
