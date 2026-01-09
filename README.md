# lucor001's QMK Corne Rev 4.1 Keymap
<img width="1367" height="693" alt="image" src="https://github.com/user-attachments/assets/907d8da2-c175-4e82-b163-0b75ec646094" />

This repository contains a fork of the qmk_userspace ([External Userspace](https://docs.qmk.fm/newbs_external_userspace)) in order to create the lucor001 QMK keymap.  Feel free to fork this repository and edit the files inside [\keyboards\crkbd\rev4_1\keymaps\lucor001](https://github.com/lucor001/qmk_userspace/tree/main/keyboards/crkbd/rev4_1/keymaps/lucor001) to your liking to create your own spin on this keymap!

## Summary:
1. This keymap was developed for the [Corne Rev 4.1](https://github.com/foostan/crkbd) by foostan.
1. It is heavily inspired by [Miryoku](https://github.com/manna-harbour/miryoku).  This was where I started before doing a complete rewrite.
1. Home row mods have been implemented by the [SM_TD](https://github.com/stasmarkin/sm_td) module by stasmarkin which seems to provide better accuracy.  This module is linked inside this repository.
1. Base keyboard layer provides [Colmak-DH](https://colemakmods.github.io/mod-dh/) but through a double-tap (Tap Dance) QWERTY and DVORAK can also be accessed.
1. The keyboard case was printed from two separate designs: [Case](https://www.printables.com/model/910711-corne-crkbd-split-keyboard-v41-new-case-with-renfo/files) and [Magnetic Tenting Legs](https://www.printables.com/model/1106860-corne-magnetic-tenting-legs).  I needed to use my slicer to expand the magnet holes in the case as my magnets were a bit larger.
1. Low profile keycaps can be ordered for this keyboard as shown above.  I used [FK Caps](https://fkcaps.com/custom/WXW2UK) to create mine but there are other options.
![lucor001_keymap](https://github.com/user-attachments/assets/8b2c7342-3a5c-4ec1-9f9d-caee20572cfc)

## Instructions:
1. Setup your own QMK environment ([QMK Tutorial](https://docs.qmk.fm/newbs))
   - You should not need to actually fork [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware), simply cloning it locally is all you need to do and this is likely handled by `qmk setup` for you.  If by chance you actually messed up your local qmk_firmware area and need to clone it again, simply use:
    ```
    cd $HOME
    git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
    ```
1. Build the standard Corne keyboard using:
   - `qmk compile -kb crkbd/rev4_1/standard -km default`
1. If you can successfully build the standard Corne keymap then it is time to fork this repository and clone it.  Here is the complete documentation: [External Userspace](https://docs.qmk.fm/newbs_external_userspace).
   - First, fork this repository as shown in the link but do it on this repository instead of qmk/qmk_userspace.
   - Next, enable userspace in QMK config using `qmk config user.overlay_dir="$(realpath qmk_userspace)"`
   - Finally, do the following inside the QMK environment to clone this repository:
    ```
    cd $HOME
    git clone https://github.com/{myusername}/qmk_userspace.git
    qmk config user.overlay_dir="$(realpath qmk_userspace)"
    ```
1. Now you should be able to build my keymap using:
   - `qmk compile -kb crkbd/rev4_1/standard -km lucor001`
1. Assuming the compile completed successfully (there are often 2 warnings but no errors) then you can add this keymap to the external userspace build target:
   - `qmk userspace-add -kb <keyboard> -km <keymap>`
   - This will update qmk.json which will allow GitHub to actually have a build workflow and build the source for you!  You will need to push qmk.json (and any other changes) back to your fork of this repository for this to work.  See the original documentation below for additional details.
   - Also note that you can now use `qmk userspace-compile` to compile the firmware locally.
1. At this point you just need to find the firmware *crkbd_rev4_1_standard_lucor001.uf2* inside the qmk_firmware directory and flash it to both halves of your keyboard.
   - For the left half, hold down the QWERTY "Q" key while plugging in the keyboard.  This is the key 1 right from the very top left key (and may be labeled something else).  This will open up a new USB flash device, simply drag the .uf2 file to this device.  It will automatically flash the firmware and disconnect the USB flash device.  After a short wait the keyboard will reboot and should turn on and connect as a keyboard.
   - For the right half, it is the same except use the QWERTY "P" key while plugging in the keyboard.  This is the key 1 left from the very top right key (and may be labeled something else).

## TODO:

### Original QMK Userpace documentation:

<details>
    
# QMK Userspace

This is a template repository which allows for an external set of QMK keymaps to be defined and compiled. This is useful for users who want to maintain their own keymaps without having to fork the main QMK repository.

## Howto configure your build targets

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. Enable userspace in QMK config using `qmk config user.overlay_dir="$(realpath qmk_userspace)"`
1. Add a new keymap for your board using `qmk new-keymap`
    * This will create a new keymap in the `keyboards` directory, in the same location that would normally be used in the main QMK repository. For example, if you wanted to add a keymap for the Planck, it will be created in `keyboards/planck/keymaps/<your keymap name>`
    * You can also create a new keymap using `qmk new-keymap -kb <your_keyboard> -km <your_keymap>`
    * Alternatively, add your keymap manually by placing it in the location specified above.
    * `layouts/<layout name>/<your keymap name>/keymap.*` is also supported if you prefer the layout system
1. Add your keymap(s) to the build by running `qmk userspace-add -kb <your_keyboard> -km <your_keymap>`
    * This will automatically update your `qmk.json` file
    * Corresponding `qmk userspace-remove -kb <your_keyboard> -km <your_keymap>` will delete it
    * Listing the build targets can be done with `qmk userspace-list`
1. Commit your changes

## Howto build with GitHub

1. In the GitHub Actions tab, enable workflows
1. Push your changes above to your forked GitHub repository
1. Look at the GitHub Actions for a new actions run
1. Wait for the actions run to complete
1. Inspect the Releases tab on your repository for the latest firmware build

## Howto build locally

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. `cd` into this repository's clone directory
1. Set global userspace path: `qmk config user.overlay_dir="$(realpath .)"` -- you MUST be located in the cloned userspace location for this to work correctly
    * This will be automatically detected if you've `cd`ed into your userspace repository, but the above makes your userspace available regardless of your shell location.
1. Compile normally: `qmk compile -kb your_keyboard -km your_keymap` or `make your_keyboard:your_keymap`

Alternatively, if you configured your build targets above, you can use `qmk userspace-compile` to build all of your userspace targets at once.

## Extra info

If you wish to point GitHub actions to a different repository, a different branch, or even a different keymap name, you can modify `.github/workflows/build_binaries.yml` to suit your needs.

To override the `build` job, you can change the following parameters to use a different QMK repository or branch:
```
    with:
      qmk_repo: qmk/qmk_firmware
      qmk_ref: master
```

If you wish to manually manage `qmk_firmware` using git within the userspace repository, you can add `qmk_firmware` as a submodule in the userspace directory instead. GitHub Actions will automatically use the submodule at the pinned revision if it exists, otherwise it will use the default latest revision of `qmk_firmware` from the main repository.

This can also be used to control which fork is used, though only upstream `qmk_firmware` will have support for external userspace until other manufacturers update their forks.

1. (First time only) `git submodule add https://github.com/qmk/qmk_firmware.git`
1. (To update) `git submodule update --init --recursive`
1. Commit your changes to your userspace repository
</details>
