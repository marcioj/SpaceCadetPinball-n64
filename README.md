# SpaceCadetPinball

## Summary

Port of https://github.com/k4zmu2a/SpaceCadetPinball for the N64

## How to play

Install [Libdragon](https://libdragon.dev/).

Put the original game files (not included) like PINBALL.DAT and its resources inside `assets` folder. Only the PINBALL.DAT works.

Run `make -f n64.mk` to generate a `pinball.z64` rom.

The rom can be played on original hardware or LLE emulators like [ares](https://ares-emu.net/).

## Controls

| Action                | Game Controller Button |
| --------------------- | ---------------------- |
| Left Flipper key      | L button               |
| Right Flipper key     | R button               |
| Plunger key           | A button               |
| Left Table Bump key   | D-pad left             |
| Right Table Bump key  | D-pad right            |
| Bottom Table Bump key | D-pad down             |
| New Game              | Z button               |
| Toggle Pause          | Start button           |

## Thanks

- Original project contributors who decompiled the original project
- Libdragon contributors who made developing N64 games a lot easy