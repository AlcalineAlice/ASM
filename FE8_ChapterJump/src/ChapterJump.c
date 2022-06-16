#include "ChapterJump.h"

//Initializes menu. Called from chapter menu
int Jump_OnSelect(MenuProc* menu, MenuCommandProc* command) {
    ChapterJumpProc* proc = (void*) ProcStart(Proc_ChapterJump, ROOT_PROC_3);

    proc->menuIndex = 0;

    StartMenuChild(&ChapterJump_MenuDefinition, (void*) proc);

    return ME_DISABLE | ME_END | ME_PLAY_BEEP | ME_CLEAR_GFX;
}

//Handles what to do when buttons are pushed
static int JumpIdle (MenuProc* menu, MenuCommandProc* command) {
    ChapterJumpProc* const proc = (void*) menu->parent;

    //If left or right is pushed, change menuIndex accordingly
    //and refresh the menu graphics
    if (gKeyState.repeatedKeys & KEY_DPAD_LEFT) {
        if (proc->menuIndex != 0) {
            proc->menuIndex--;
            JumpDraw(menu, command);
            PlaySfx(0x6B);
        }
    }
    if (gKeyState.repeatedKeys & KEY_DPAD_RIGHT) {
        if (proc->menuIndex < 0x4E) {
            proc->menuIndex++;
            JumpDraw(menu, command);
            PlaySfx(0x6B);
        }
    }

    return ME_NONE;
}

<<<<<<< HEAD
//Handles chapter jumping
static int JumpEffect(MenuProc* menu, MenuCommandProc* command) {
    ChapterJumpProc* const proc = (void*) menu->parent;
=======
static int JumpEvent(MenuProc* menu, MenuCommandProc* command) {
    struct ChapterJumpProc* const proc = (void*) menu->parent;
>>>>>>> 5812c890e2559297e9e3952a12cdefebe0cbefc9

    //Move template event to RAM location
    memcpy(gRAMChapterJumpEvent, &gChapterJumpEvent, sizeof(ChapterJumpEvent));

    //Set chapter index to jump to
    gRAMChapterJumpEvent->chapterIndex = proc->menuIndex;

    //Optional extra event before jump
    u32* debugEventPointer = DebugEvent[proc->menuIndex].eventPointer;
    if (debugEventPointer) {
        gRAMChapterJumpEvent->prepEventPointer = debugEventPointer;
    }

    //Run the event
    CallMapEventEngine(gRAMChapterJumpEvent, 1);

    return ME_END;
}

//Draws the UI
static int JumpDraw(MenuProc* menu, MenuCommandProc* command) {
    ChapterJumpProc* const proc = (void*) menu->parent;
    u16* const out = gBg0MapBuffer + TILEMAP_INDEX(command->xDrawTile,
                                                   command->yDrawTile);

    //Get chapter title ID
    u16 title = GetChapterDefinition(proc->menuIndex)->titleID;

    //Initialize text
    Text_Clear(&command->text);
    Text_SetColorId(&command->text, TEXT_COLOR_NORMAL);
<<<<<<< HEAD

    //Display chapter title if it's set
    if (!title) {
        Text_SetXCursor(&command->text, 0x8);
=======
    if (title == 0) {
        Text_SetXCursor(&command->text, 0xC);
>>>>>>> 5812c890e2559297e9e3952a12cdefebe0cbefc9
        Text_DrawNumberOr2Dashes(&command->text, proc->menuIndex);
    }
    //Otherwise, display the chapter ID
    else {
        Text_DrawString(&command->text, GetStringFromIndex(title));
    }

    Text_Display(&command->text, out);
    return ME_NONE;
}
