#ifndef ___KEY__PH___
#define ___KEY__PH___

/// Checks CONTROL, SHIFT, ALT are notpressed
CU_EXT_API BOOL IsKeyNoShift();

/// Checks CONTROL, SHIFT, ALT are pressed
CU_EXT_API BOOL IsKeyAllShift();

/// Checks CONTROL Key alone is pressed
CU_EXT_API BOOL IsKeyCtrl();

/// Checks CONTROL Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyCtrl_();

/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed
CU_EXT_API BOOL IsKeyCtrlS();

/// Checks CONTROL, SHIFT Key is pressed, and ALT is pressed or not pressed
CU_EXT_API BOOL IsKeyCtrlS_();

/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed
CU_EXT_API BOOL IsKeyCtrlA();

/// Checks CONTROL, ALT Key is pressed, and SHIFT is pressed or not pressed
CU_EXT_API BOOL IsKeyCtrlA_();

/// Checks CONTROL Key is pressed, SHIFT is not pressed and ALT is pressed or not
CU_EXT_API BOOL IsKeyCtrl_S();

/// Checks CONTROL Key is pressed, ALT are not pressed and SHIFT is pressed or not
CU_EXT_API BOOL IsKeyCtrl_A();

/// Checks SHIFT Key alone is pressed
CU_EXT_API BOOL IsKeyShift();

/// Checks SHIFT Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyShift_();

/// Checks SHIFT Key is pressed, CONTROL is not pressed and ALT is pressed or not
CU_EXT_API BOOL IsKeyShift_C();

/// Checks SHIFT Key is pressed, ALT are not pressed and CONTROL is pressed or not
CU_EXT_API BOOL IsKeyShift_A();

/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed
CU_EXT_API BOOL IsKeyShiftC();

/// Checks SHIFT, CONTROL Key is pressed, and ALT is pressed or not pressed
CU_EXT_API BOOL IsKeyShiftC_();

/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed
CU_EXT_API BOOL IsKeyShiftA();

/// Checks SHIFT, ALT Key is pressed, and CONTROL is pressed or not pressed
CU_EXT_API BOOL IsKeyShiftA_();

/// Checks ALT Key alone is pressed
CU_EXT_API BOOL IsKeyAlt();

/// Checks ALT Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyAlt_();

/// Checks ALT Key is pressed, CONTROL is not pressed and SHIFT is pressed or not
CU_EXT_API BOOL IsKeyAlt_C();

/// Checks ALT Key is pressed, SHIFT are not pressed and CONTROL is pressed or not
CU_EXT_API BOOL IsKeyAlt_S();

/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed
CU_EXT_API BOOL IsKeyAltS();

/// Checks ALT, SHIFT Key is pressed, and CONTROL is pressed or not pressed
CU_EXT_API BOOL IsKeyAltS_();

/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed
CU_EXT_API BOOL IsKeyAltC();

/// Checks ALT, CONTROL Key is pressed, and SHIFT is pressed or not pressed
CU_EXT_API BOOL IsKeyAltC_();

/// Checks LBUTTON Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyLButton_();

/// Checks RBUTTON Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyRButton_();

/// Checks MBUTTON Key is pressed. The other shift keys can be pressed or not
CU_EXT_API BOOL IsKeyMButton_();

#include "key.win.h"

#endif  ___KEY__PH___