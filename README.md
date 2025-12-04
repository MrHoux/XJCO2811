# FeeL Project Overview

FeeL is a social media application featuring a video player. The application name “FeeL’’ reflects our design vision. The letter “F’’ stands for “freedom’’ or “freestyle,’’ values that many young users seek in digital spaces. The capital “L’’ represents “Life,’’ symbolizing energy, continuity, and real emotional experience. Together, the name expresses our intention to build a platform that supports honest self-expression and meaningful social connection.
The consist of program: 

- `FeeL.cpp`: Application entry point and main UI assembly (home feed, friends, chat, post, profile, settings), media controls, language handling, share dialogs, and navigation icons.
- `resources.qrc`: Qt resource collection mapping assets (avatars, logo, navigation icons) into the application.
- `the.pro`: Qt project configuration listing sources, headers, resources, translations, and compiler settings.
- `chatwindow.cpp/h`: Chat list and thread views, message seed data, avatar rendering, and share-message hook.
- `postpage.cpp/h`: Post creation mock (photo/video), recording timer, overlays for publish/album prompts, capture controls.
- `detailwindow.cpp/h`: Settings detail subpages (audio, notifications, privacy, timezone, other, share/rate/help/about) and back/language signals.
- `settingwindow.cpp/h`: Settings main page (profile card, feature/settings/about sections, logout) and share-profile signal.
- `friends_data.h`: Data structure for friend/profile info and gallery references.
- `friendwindow.cpp/h`: Simple friend list window and profile handoff.
- `profilewindow.cpp/h`: Simple profile display window used by friend window.
- `the_button.cpp/h`, `the_player.cpp/h`: Legacy video button/player utilities used by the feed.
- `chatwindow`, `detailwindow`, `postpage`, `settingwindow` headers/cpps: Each pair defines UI and logic for its respective module as listed above.
- `assets/`: Images for avatars, logo, and navigation icons (light/dark variants).