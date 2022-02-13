#ifndef CONFIG
#define CONFIG

#define SCREEN_ADDRESS 0x3D ///< See datasheet for Address; 0x3D / 0x3C

#define INTERRUPT1 2 //Pin for UP button
#define INTERRUPT2 4 //Pin for Down button
#define INTERRUPT3 18 //Pin for Confirm button

#define DEBOUNCE 400 //Debounce time

#endif // CONFIG
