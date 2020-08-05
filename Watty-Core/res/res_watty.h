#pragma once
//AUTO-GENERATED FILE, EDIT AT YOUR OWN RISK

#include <Resource.h>
struct RawWattyResources {
	//AUTO-BEGIN-RES
	//
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
static const unsigned char fonts_Roboto_LICENSE_txt[];;
static const unsigned fonts_Roboto_LICENSE_txt_size;
;
static const unsigned char fonts_Roboto_Roboto_Black_ttf[];;
static const unsigned fonts_Roboto_Roboto_Black_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_BlackItalic_ttf[];;
static const unsigned fonts_Roboto_Roboto_BlackItalic_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_LightItalic_ttf[];;
static const unsigned fonts_Roboto_Roboto_LightItalic_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_Medium_ttf[];;
static const unsigned fonts_Roboto_Roboto_Medium_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_MediumItalic_ttf[];;
static const unsigned fonts_Roboto_Roboto_MediumItalic_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_Thin_ttf[];;
static const unsigned fonts_Roboto_Roboto_Thin_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_ThinItalic_ttf[];;
static const unsigned fonts_Roboto_Roboto_ThinItalic_ttf_size;
;
static const unsigned char fonts_arial_ttf[];;
static const unsigned fonts_arial_ttf_size;
;
static const unsigned char fonts_consola_ttf[];;
static const unsigned fonts_consola_ttf_size;
;
static const unsigned char shaders_default_frag[];;
static const unsigned shaders_default_frag_size;
;
static const unsigned char shaders_default_vert[];;
static const unsigned shaders_default_vert_size;
;
static const unsigned char shaders_default_es3_frag[];;
static const unsigned shaders_default_es3_frag_size;
;
static const unsigned char shaders_default_es3_vert[];;
static const unsigned shaders_default_es3_vert_size;
;
static const unsigned char textures_error_texture_png[];;
static const unsigned textures_error_texture_png_size;

	//AUTO-END-RES
static void Init() {
	//AUTO-BEGIN-INIT
	//
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
Resources::all.push_back(new Resource("fonts/Roboto/LICENSE.txt", fonts_Roboto_LICENSE_txt, fonts_Roboto_LICENSE_txt_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-Black.ttf", fonts_Roboto_Roboto_Black_ttf, fonts_Roboto_Roboto_Black_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-BlackItalic.ttf", fonts_Roboto_Roboto_BlackItalic_ttf, fonts_Roboto_Roboto_BlackItalic_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-LightItalic.ttf", fonts_Roboto_Roboto_LightItalic_ttf, fonts_Roboto_Roboto_LightItalic_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-Medium.ttf", fonts_Roboto_Roboto_Medium_ttf, fonts_Roboto_Roboto_Medium_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-MediumItalic.ttf", fonts_Roboto_Roboto_MediumItalic_ttf, fonts_Roboto_Roboto_MediumItalic_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-Thin.ttf", fonts_Roboto_Roboto_Thin_ttf, fonts_Roboto_Roboto_Thin_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-ThinItalic.ttf", fonts_Roboto_Roboto_ThinItalic_ttf, fonts_Roboto_Roboto_ThinItalic_ttf_size));
;
Resources::all.push_back(new Resource("fonts/arial.ttf", fonts_arial_ttf, fonts_arial_ttf_size));
;
Resources::all.push_back(new Resource("fonts/consola.ttf", fonts_consola_ttf, fonts_consola_ttf_size));
;
Resources::all.push_back(new Resource("shaders/default.frag", shaders_default_frag, shaders_default_frag_size));
;
Resources::all.push_back(new Resource("shaders/default.vert", shaders_default_vert, shaders_default_vert_size));
;
Resources::all.push_back(new Resource("shaders/default_es3.frag", shaders_default_es3_frag, shaders_default_es3_frag_size));
;
Resources::all.push_back(new Resource("shaders/default_es3.vert", shaders_default_es3_vert, shaders_default_es3_vert_size));
;
Resources::all.push_back(new Resource("textures/error_texture.png", textures_error_texture_png, textures_error_texture_png_size));

	//AUTO-END-INIT
}
};
