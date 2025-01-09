/*******************************************************************/
/*    Copyright (c) 1989-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#include "constructors_examples.hxx"

#include "acis/api.err"
#include "acis/ckoutcom.hxx"
#include "acis/cstrapi.hxx"
#include "acis/kernapi.hxx"
#include "acis/rnd_api.hxx"
#include "acis/transf.hxx"

outcome aei_TEXT_FROM_WIRE_HELLO(ENTITY_LIST& output_ents, AcisOptions* ptrAcisOpt) {
#ifdef _MSC_VER
    BODY* hello_en = NULL;
    BODY* hello_ch = NULL;

    API_BEGIN

    // Note: The make function throws an error if the font is not installed on the operating system.

    const char* fnt1_name = "Calibri";
    const char* fnt2_name = "MingLiU";

    const unsigned fnt_style = formatted_text::FS_BOLD | formatted_text::FS_ITALIC;

    formatted_text::font myfont1 = formatted_text::make_font(fnt1_name, fnt_style);
    formatted_text::font myfont2 = formatted_text::make_font(fnt2_name, fnt_style);

    // Make formatted_text objects using the font objects and height.

    const unsigned height = 10;
    formatted_text text1("Hello World!", myfont1, height);
    wchar_t str_ch[6] = {wchar_t(20320), wchar_t(22909), wchar_t(19990), wchar_t(30028), wchar_t(33), wchar_t(0)};

    formatted_text text2(str_ch, myfont2, height);

    // Make wire bodies from formatted_text objects.

    outcome result1 = api_make_wire(text1, hello_en);
    check_outcome(result1);

    outcome result2 = api_make_wire(text2, hello_ch);
    check_outcome(result2);

    SPAtransf move = translate_transf(SPAvector(0, -15, 0));
    check_outcome(api_transform_entity(hello_ch, move));
    check_outcome(api_change_body_trans(hello_ch, NULL));

    // Set the Chinese Hello World color cyan
    rgb_color cyan(0.0, 1.0, 1.0);
    check_outcome(api_rh_set_entity_rgb(hello_ch, cyan));
    // Set the English Hello World color magenta
    rgb_color magenta(1.0, 0.0, 1.0);
    check_outcome(api_rh_set_entity_rgb(hello_en, magenta));

    API_END
    if(result.ok()) {
        output_ents.add(hello_en);
        output_ents.add(hello_ch);
    }
    return result;
#else
    return outcome(API_FAILED);
#endif
}
