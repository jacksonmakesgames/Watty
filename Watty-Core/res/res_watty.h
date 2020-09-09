#pragma once
//AUTO-GENERATED FILE, EDIT AT YOUR OWN RISK

#include <Resource.h>
struct RawWattyResources {
	//AUTO-BEGIN-RES
	//
static const unsigned char fonts_Roboto_LICENSE_txt[];;
static const unsigned fonts_Roboto_LICENSE_txt_size;
;
static const unsigned char fonts_Roboto_Roboto_Medium_ttf[];;
static const unsigned fonts_Roboto_Roboto_Medium_ttf_size;
;
static const unsigned char fonts_Roboto_Roboto_MediumItalic_ttf[];;
static const unsigned fonts_Roboto_Roboto_MediumItalic_ttf_size;
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

	//AUTO-END-RES
static void Init() {
	//AUTO-BEGIN-INIT
	//
Resources::all.push_back(new Resource("fonts/Roboto/LICENSE.txt", fonts_Roboto_LICENSE_txt, fonts_Roboto_LICENSE_txt_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-Medium.ttf", fonts_Roboto_Roboto_Medium_ttf, fonts_Roboto_Roboto_Medium_ttf_size));
;
Resources::all.push_back(new Resource("fonts/Roboto/Roboto-MediumItalic.ttf", fonts_Roboto_Roboto_MediumItalic_ttf, fonts_Roboto_Roboto_MediumItalic_ttf_size));
;
Resources::all.push_back(new Resource("shaders/default.frag", shaders_default_frag, shaders_default_frag_size));
;
Resources::all.push_back(new Resource("shaders/default.vert", shaders_default_vert, shaders_default_vert_size));
;
Resources::all.push_back(new Resource("shaders/default_es3.frag", shaders_default_es3_frag, shaders_default_es3_frag_size));
;
Resources::all.push_back(new Resource("shaders/default_es3.vert", shaders_default_es3_vert, shaders_default_es3_vert_size));

	//AUTO-END-INIT
}
};
