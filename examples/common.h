#include "../native_menu_bar.h"

#define UNUSED(x) (void)(x)

/* Menu item IDs */
nmb_Handle g_hFileNew = 0;
nmb_Handle g_hFileOpen = 0;
nmb_Handle g_hFileSave = 0;
nmb_Handle g_hFileEnabler = 0;
nmb_Handle g_hFileEnablee = 0;
nmb_Handle g_hEditCopy = 0;
nmb_Handle g_hEditPaste = 0;
nmb_Handle g_hHelpAbout = 0;

static void createExampleMenuBar(void* nativeHandle)
{
    nmb_setup(nativeHandle);

    nmb_Handle hEditMenu = nmb_appendMenu(NULL, "Edit");
    nmb_Handle hHelpMenu = nmb_appendMenu(NULL, "Help öäĂĹŸ");
    nmb_Handle hFileMenu = nmb_insertMenu(NULL, 0, "File"); /* example inserting at a specific position in the menu bar */

    /* File menu */
    g_hFileNew = nmb_appendMenuItem(hFileMenu, "_New");
    g_hFileOpen = nmb_appendMenuItem(hFileMenu, "_Open...");
    g_hFileSave = nmb_appendMenuItem(hFileMenu, "_Save");
    nmb_appendCheckMenuItem(hFileMenu, "Check Me");
    nmb_appendSeparator(hFileMenu);
    g_hFileEnabler = nmb_appendMenuItem(hFileMenu, "Enabler");
    g_hFileEnablee = nmb_appendMenuItem(hFileMenu, "Enablee");

    /* Edit menu */
    g_hEditCopy = nmb_appendMenuItem(hEditMenu, "_Copy");
    g_hEditPaste = nmb_appendMenuItem(hEditMenu, "_Paste");

    nmb_Handle submenu1 = nmb_insertMenu(hFileMenu, 1, "Inserted Submenu");
    nmb_appendCheckMenuItem(submenu1, "Item 1");
    nmb_appendCheckMenuItem(submenu1, "Item 2");
    nmb_appendCheckMenuItem(submenu1, "Item 3");
    nmb_insertMenuItem(submenu1, -2, "Inserted Menu");
    nmb_insertSeparator(submenu1, -3);
    nmb_insertSeparator(hFileMenu, 2);
    nmb_insertSeparator(hFileMenu, 1);

    nmb_Handle submenu2 = nmb_appendMenu(hEditMenu, "Submenu");
    nmb_appendMenuItem(submenu2, "Submenu Item 1");

    /* Help menu */
    g_hHelpAbout = nmb_appendMenuItem(hHelpMenu, "About...");
}

static void exampleEventHandler()
{
    nmb_Event e;
    while (nmb_pollEvent(&e))
    {
        if (e.sender == g_hFileNew)
        {
            printf("New file selected\n");
        }
        else if (e.sender == g_hFileOpen)
        {
            printf("Open file selected\n");
        }
        else if (e.sender == g_hFileSave)
        {
            printf("Save file selected\n");
        }
        else if (e.sender == g_hFileEnabler)
        {
            nmb_setMenuItemEnabled(g_hFileEnablee, !nmb_isMenuItemEnabled(g_hFileEnablee));
        }
        else if (e.sender == g_hEditCopy)
        {
            printf("Copy selected\n");
        }
        else if (e.sender == g_hEditPaste)
        {
            printf("Paste selected\n");
        }
        else if (e.sender == g_hHelpAbout)
        {
            printf("Native Menu Bar Demo\nVersion 1.0\n");
        }
        else
        {
            nmb_setMenuItemChecked(e.sender, !nmb_isMenuItemChecked(e.sender));
        }
    }
}
