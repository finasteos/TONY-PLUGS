cmake_minimum_required(VERSION 3.22)

project(TonyPlugs VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Fetch JUCE 8.x ──
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.4   # Pin to stable release
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(JUCE)

# ── Plugin Target ──
juce_add_plugin(TonyPlugs
    COMPANY_NAME          "TonyPlugs"
    IS_SYNTH              FALSE
    NEEDS_MIDI_INPUT      FALSE
    NEEDS_MIDI_OUTPUT     FALSE
    IS_MIDI_EFFECT        FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS  TRUE
    COPY_PLUGIN_AFTER_BUILD      TRUE
    PLUGIN_MANUFACTURER_CODE     Tnpl
    PLUGIN_CODE                  Tn01
    FORMATS               VST3 AU Standalone    # NO AAX!
    PRODUCT_NAME          "Tony Plugs"
    BUNDLE_ID             "com.tonyplugs.plugin"
    MICROPHONE_PERMISSION_ENABLED FALSE
    DESCRIPTION           "La Linea inspired VST plugin"
)

# ── Source Files ──
target_sources(TonyPlugs
    PRIVATE
        src/PluginProcessor.cpp
        src/PluginEditor.cpp
        src/LookAndFeel/LinusLookAndFeel.cpp
        src/LookAndFeel/LinusWaveformComponent.cpp
        src/LookAndFeel/LineManager.cpp
        src/LookAndFeel/LineMutations/LineMutations.cpp
)

# ── Include Directories ──
target_include_directories(TonyPlugs
    PRIVATE
        src
)

# ── JUCE Module Dependencies ──
target_link_libraries(TonyPlugs
    PRIVATE
        juce::juce_audio_utils
        juce::juce_audio_processors
        juce::juce_dsp
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

# ── Compile Definitions ──
target_compile_definitions(TonyPlugs
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
)
