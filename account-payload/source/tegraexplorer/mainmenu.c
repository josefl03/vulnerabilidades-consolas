#include "mainmenu.h"
#include "../gfx/gfx.h"
#include "../gfx/gfxutils.h"
#include "../gfx/menu.h"
#include "tools.h"
#include "../hid/hid.h"
#include "../fs/menus/explorer.h"
#include <utils/btn.h>
#include <storage/nx_sd.h>
#include "tconf.h"
#include "../keys/keys.h"
#include "../storage/mountmanager.h"
#include "../storage/gptmenu.h"
#include "../storage/emummc.h"
#include <utils/util.h>
#include "../fs/fsutils.h"
#include <soc/fuse.h>
#include "../utils/utils.h"
#include "../config.h"
#include "../fs/readers/folderReader.h"
#include <string.h>
#include <mem/heap.h>
#include "../fs/menus/filemenu.h"
#include <display/di.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INCLUDE_BUILTIN_SCRIPTS 1
//#define SCRIPT_ONLY 1

#ifdef INCLUDE_BUILTIN_SCRIPTS
#include "../../build/AccountPayload/script/builtin.h"
#endif

extern hekate_config h_cfg;

enum {
    #ifndef SCRIPT_ONLY
    MainExplore = 0,
    MainBrowseSd,
    MainMountSd,
    MainBrowseEmmc,
    MainBrowseEmummc,
    MainTools,
    MainPartitionSd,
    MainViewKeys,
    MainViewCredits,
    MainExit,
    #else 
    MainExit = 0,
    #endif
    MainPowerOff,
    MainRebootRCM,
    MainRebootNormal,
    MainRebootHekate,
    MainRebootAMS,
    MainScripts,
};

MenuEntry_t mainMenuEntries[] = {
    #ifndef SCRIPT_ONLY
    [MainExplore] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "-- Explore --"},
    [MainBrowseSd] = {.optionUnion = COLORTORGB(COLOR_GREEN), .name = "Browse SD"},
    [MainMountSd] = {.optionUnion = COLORTORGB(COLOR_YELLOW)}, // To mount/unmount the SD
    [MainBrowseEmmc] = {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "Browse EMMC"},
    [MainBrowseEmummc] = {.optionUnion = COLORTORGB(COLOR_BLUE), .name = "Browse EMUMMC"},
    [MainTools] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Tools --"},
    [MainPartitionSd] = {.optionUnion = COLORTORGB(COLOR_ORANGE), .name = "Partition the sd"},
    [MainViewKeys] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .name = "View dumped keys"},
    [MainViewCredits] = {.optionUnion = COLORTORGB(COLOR_YELLOW), .name = "Credits"},
    [MainExit] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Exit --"},
    #else 
    [MainExit] = {.optionUnion = COLORTORGB(COLOR_WHITE), .name = "\n-- Exit --"},
    #endif
    [MainPowerOff] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Power off"},
    [MainRebootRCM] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to RCM"},
    [MainRebootNormal] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot normally"},
    [MainRebootHekate] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to bootloader/update.bin"},
    [MainRebootAMS] = {.optionUnion = COLORTORGB(COLOR_VIOLET), .name = "Reboot to atmosphere/reboot_payload.bin"},
    [MainScripts] = {.optionUnion = COLORTORGB(COLOR_WHITE) | SKIPBIT, .name = "\n-- Scripts --"}
};

void HandleSD(){
    gfx_clearscreen();
    TConf.curExplorerLoc = LOC_SD;
    if (!sd_mount() || sd_get_card_removed()){
        gfx_printf("Sd is not mounted!");
        hidWait();
    }
    else
        FileExplorer("sd:/");
}

void HandleEMMC(){
   GptMenu(MMC_CONN_EMMC);
}

void HandleEMUMMC(){
    GptMenu(MMC_CONN_EMUMMC);
}

void ViewKeys(){
    gfx_clearscreen();
    for (int i = 0; i < 3; i++){
        gfx_printf("\nBis key 0%d:   ", i);
        PrintKey(dumpedKeys.bis_key[i], AES_128_KEY_SIZE * 2);
    }
    
    gfx_printf("\nMaster key 0: ");
    PrintKey(dumpedKeys.master_key, AES_128_KEY_SIZE);
    gfx_printf("\nHeader key:   ");
    PrintKey(dumpedKeys.header_key, AES_128_KEY_SIZE * 2);
    gfx_printf("\nSave mac key: ");
    PrintKey(dumpedKeys.save_mac_key, AES_128_KEY_SIZE);

    u8 fuseCount = 0;
    for (u32 i = 0; i < 32; i++){
        if ((fuse_read_odm(7) >> i) & 1)
            fuseCount++;
    }

    gfx_printf("\n\nPkg1 ID: '%s'\nFuse count: %d", TConf.pkg1ID, fuseCount);

    hidWait();
}

void ViewCredits(){
    gfx_clearscreen();
    gfx_printf("\nTegraexplorer v%d.%d.%d\nBy SuchMemeManySkill\n\nBased on Lockpick_RCM & Hekate, from shchmue & CTCaer\n\n\n", LP_VER_MJ, LP_VER_MN, LP_VER_BF);

    if (hidRead()->r)
        gfx_printf("%k\"I'm not even sure if it works\" - meme", COLOR_ORANGE);

    hidWait();
}

extern bool sd_mounted;
extern bool is_sd_inited;
extern int launch_payload(char *path);

void RebootToAMS(){
    launch_payload("sd:/atmosphere/reboot_payload.bin");
}

void RebootToHekate(){
    launch_payload("sd:/bootloader/update.bin");
}

void MountOrUnmountSD(){
    gfx_clearscreen();
    if (sd_mounted)
        sd_unmount();
    else if (!sd_mount())
        hidWait();
}

menuPaths mainMenuPaths[] = {
    #ifndef SCRIPT_ONLY
    [MainBrowseSd] = HandleSD,
    [MainMountSd] = MountOrUnmountSD,
    [MainBrowseEmmc] = HandleEMMC,
    [MainBrowseEmummc] = HandleEMUMMC,
    [MainPartitionSd] = FormatSD,
    [MainViewKeys] = ViewKeys,
    [MainViewCredits] = ViewCredits,
    #endif
    [MainRebootAMS] = RebootToAMS,
    [MainRebootHekate] = RebootToHekate,
    [MainRebootRCM] = reboot_rcm,
    [MainPowerOff] = power_off,
    [MainRebootNormal] = reboot_normal,
};

char** find_strings(char* start_address, int max_strings, int min_length, int* found_count);

void ShowCustomImage(){

    display_backlight_brightness(70, 0);

    gfx_box(0, 0, 1280, 720, 0xFF1B1B1B);

    gfx_con_setpos(0, 0);

    // 8000000000000010
    char* file_010 = loadFile("sd:/8000000000000010");

    gfx_printf("\n\n\n");
    gfx_printf("    Nombre de consola:\n     - %s\n", file_010 + 0x1BA950);

    gfx_printf("\n\n\n");
    gfx_printf("    Numeros de serie:\n     - ");
    showProtected(file_010 + 0x1BD507);
    gfx_printf("\n     - ");
    showProtected(file_010 + 0x1BD547);
    gfx_printf("\n");

    gfx_printf("\n\n\n");
    gfx_printf("    Conexiones WiFi:\n     - ");

    show(file_010 + 0x1C48BC);
    gfx_printf(" | Password: ");
    showProtected(file_010 + 0x1C48E8);
    gfx_printf("\n     - ");
    
    show(file_010 + 0x1C4CBC);
    gfx_printf("    | Password: ");
    showProtected(file_010 + 0x1C4CE8);
    gfx_printf("\n     - ");
    
    show(file_010 + 0x1C50BD);
    gfx_printf("  | Password: ");
    showProtected(file_010 + 0x1C50E8);
    gfx_printf("\n");

    // 0000000000000057

    char* file_057 = loadFile("sd:/0000000000000057");


    gfx_printf("\n\n\n");
    gfx_printf("    Servidor:\n     - ");
    show(file_057 + 0x5800C);
    gfx_printf("\n");

    gfx_printf("    Usuario:\n     - ");
    show(file_057 + 0x5810C);
    gfx_printf("\n");

    gfx_printf("    Contraseña:\n     - ");
    showMaxProtected(file_057 + 0x5818C);
    gfx_printf("\n");

    // 8000000000001060


    char* file_1060 = loadFile("sd:/8000000000001060");

    gfx_printf("\n\n\n");
    gfx_printf("    Servidor:\n     - ");
    show(file_1060 + 0x1098214);
    gfx_printf("\n");

    gfx_printf("    Correo:\n     - ");
    show(file_1060 + 0x1098314);
    gfx_printf("\n");

    gfx_printf("    Contraseña:\n     - ");
    showMaxProtected(file_1060 + 0x1098394);
    gfx_printf("\n");

    // Find console name
    
}

void showProtected(char* address){
    for (int i = 0; i < 0x13; i++){
        if (address[i] == 0x00)
            break;

        if (i < 6)
            gfx_printf("%c", address[i]);
        else
            gfx_printf(".");
    }
}


void showMaxProtected(char* address){
    for (int i = 0; i < 0x13; i++){
        if (address[i] == 0x00)
            break;

        if (i >= 4 && i <= 8)
            gfx_printf("%c", address[i]);
        else
            gfx_printf(".");
    }
}

void show(char* address){
    for (int i = 0; i < 0x50; i++){
        if (address[i] == 0x00)
            break;

        gfx_printf("%c", address[i]);
    }
}

char* loadFile(const char* path){
    //Get the image size
    FILINFO finfo;
    FRESULT file_info = f_stat(path, &finfo);
    if (file_info){
        gfx_printf("Error opening image file!");
        return NULL;
    }

    //Read the entire image
    FIL f;
    FRESULT file_open = f_open(&f, path, FA_READ);
    if (file_open){
        gfx_printf("Error opening image file!");
        return NULL;
    }

    u32 file_size = finfo.fsize;
    u8 *buf = malloc(file_size);
    if (!buf){
        gfx_printf("Error allocating memory for image!");
        return NULL;
    }

    u32 br;
    FRESULT file_read = f_read(&f, buf, file_size, &br);
    if (file_read){
        gfx_printf("Error reading image file!");
        free(buf);
        return NULL;
    }

    f_close(&f);
    return (char*)buf;
}


void EnterMainMenu(){
    int res = 0;
    while (1){
        if (sd_get_card_removed())
            sd_unmount();

        #ifndef SCRIPT_ONLY
        // -- Explore --
        mainMenuEntries[MainBrowseSd].hide = !sd_mounted;
        mainMenuEntries[MainMountSd].name = (sd_mounted) ? "Unmount SD" : "Mount SD";
        mainMenuEntries[MainBrowseEmummc].hide = (!emu_cfg.enabled || !sd_mounted);

        // -- Tools --
        mainMenuEntries[MainPartitionSd].hide = (!is_sd_inited || sd_get_card_removed());
        mainMenuEntries[MainViewKeys].hide = !TConf.keysDumped;

        // -- Exit --
        mainMenuEntries[MainRebootAMS].hide = (!sd_mounted || !FileExists("sd:/atmosphere/reboot_payload.bin"));
        mainMenuEntries[MainRebootHekate].hide = (!sd_mounted || !FileExists("sd:/bootloader/update.bin"));
        mainMenuEntries[MainRebootRCM].hide = h_cfg.t210b01;
        #endif
        // -- Scripts --
        #ifndef INCLUDE_BUILTIN_SCRIPTS
        mainMenuEntries[MainScripts].hide = (!sd_mounted || !FileExists("sd:/tegraexplorer/scripts"));
        #else
        mainMenuEntries[MainScripts].hide = ((!sd_mounted || !FileExists("sd:/tegraexplorer/scripts")) && !EMBEDDED_SCRIPTS_LEN);
        #endif

        Vector_t ent = newVec(sizeof(MenuEntry_t), ARRAY_SIZE(mainMenuEntries));
        ent.count = ARRAY_SIZE(mainMenuEntries);
        memcpy(ent.data, mainMenuEntries, sizeof(MenuEntry_t) * ARRAY_SIZE(mainMenuEntries));
        Vector_t scriptFiles = {0};
        u8 hasScripts = 0;

        #ifdef INCLUDE_BUILTIN_SCRIPTS
        for (int i = 0; i < EMBEDDED_SCRIPTS_LEN; i++){
            MenuEntry_t m = {.name = embedded_scripts_g[i].name, .optionUnion = COLORTORGB(COLOR_BLUE), .icon = 128};
            vecAdd(&ent, m);
        }
        #endif

        if (sd_mounted && FileExists("sd:/tegraexplorer/scripts")){
            scriptFiles = ReadFolder("sd:/tegraexplorer/scripts", &res);
            if (!res){
                if (!scriptFiles.count){
                    FREE(scriptFiles.data);
                    mainMenuEntries[MainScripts].hide = 1;
                }
                else {
                    hasScripts = 1;
                    vecForEach(FSEntry_t*, scriptFile, (&scriptFiles)){
                        if (!scriptFile->isDir && StrEndsWith(scriptFile->name, ".te")){
                            MenuEntry_t a = MakeMenuOutFSEntry(*scriptFile);
                            vecAdd(&ent, a);
                        }
                    }

                    if (ent.count == ARRAY_SIZE(mainMenuEntries)){
                        clearFileVector(&scriptFiles);
                        hasScripts = 0;
                        mainMenuEntries[MainScripts].hide = 1;
                    }
                }
            }
        }
        

        gfx_clearscreen();
        gfx_putc('\n');
        
        res = newMenu(&ent, res, 79, 30, (ent.count == ARRAY_SIZE(mainMenuEntries)) ? ALWAYSREDRAW : ALWAYSREDRAW | ENABLEPAGECOUNT, ent.count - ARRAY_SIZE(mainMenuEntries));
        if (res < MainScripts && mainMenuPaths[res] != NULL)
            mainMenuPaths[res]();
        #ifndef INCLUDE_BUILTIN_SCRIPTS
        else if (hasScripts){
        #else
        else {
            if (res - ARRAY_SIZE(mainMenuEntries) < EMBEDDED_SCRIPTS_LEN){
                char *script = embedded_scripts_g[res - ARRAY_SIZE(mainMenuEntries)].script;
                RunScriptString(script, strlen(script));
            }
            else {
            #endif
                vecDefArray(MenuEntry_t*, entArray, ent);
                MenuEntry_t entry = entArray[res];
                FSEntry_t fsEntry = {.name = entry.name, .sizeUnion = entry.sizeUnion};
                RunScript("sd:/tegraexplorer/scripts", fsEntry);
            #ifdef INCLUDE_BUILTIN_SCRIPTS
            }
            #endif
        }

        if (hasScripts){
            clearFileVector(&scriptFiles);
        }

        free(ent.data);
    }
}

