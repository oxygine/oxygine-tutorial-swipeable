#!/usr/bin/env sh
adb install -r bin/Swipeable-debug.apk
adb shell am start -n org.oxygine.Swipeable/org.oxygine.Swipeable.MainActivity
