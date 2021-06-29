## Notice this is not finished

# UI's In Slimey Land MAN!
SLM offers 3 different UI components they are "BUTTON", "TEXTBOX" and "UIBOX". UIBOX is A container for the other components along with images and text. Once added to A UIBOX because pointers are passed to the components they can still be changed after being added. The UIBOX can be setup by hand calling the add functions. But it is easier to use the SLM UI EDITOR instead. This guide will also tell you about the UIBOX functions to create them by hand.

# Properties of A UIBOX
The UIBOX has A 2 properties and 4 in the UI EDITOR. X and Y offset determine how many pixels from the top left of the screen that the UIBOX is offseted from the default values are {X:64,Y:64}. In the UI EDITOR you can also choose to make it global and set A key that will open and close it called the trigger key. Also in the UI EDITOR you can add UIBOX data which is data put in the struct used for the UIBOX. The string type offered as A type for UI DATA is converted to char* when exported.

## Example of UIBOX offsets
![Example UIBOX](https://raw.githubusercontent.com/8-BIT-DEV/Slimey-Land-MAN/main/ui%20guide%20src/example%20ui%20box.png)

# The UI EDITOR
