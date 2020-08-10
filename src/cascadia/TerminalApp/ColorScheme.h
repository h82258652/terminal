/*++
Copyright (c) Microsoft Corporation
Licensed under the MIT license.

Module Name:
- ColorScheme.hpp

Abstract:
- A color scheme is a single set of colors to use as the terminal colors. These
    schemes are named, and can be used to quickly change all the colors of the
    terminal to another scheme.

Author(s):
- Mike Griese - March 2019

--*/
#pragma once
#include "TerminalSettings.h"
#include "../../inc/conattrs.hpp"

#include "ColorScheme.g.h"

// fwdecl unittest classes
namespace TerminalAppLocalTests
{
    class SettingsTests;
    class ColorSchemeTests;
};

namespace winrt::TerminalApp::implementation
{
    struct ColorScheme : ColorSchemeT<ColorScheme>
    {
    public:
        ColorScheme();
        ColorScheme(hstring name, uint32_t defaultFg, uint32_t defaultBg, uint32_t cursorColor);
        ~ColorScheme();

        void ApplyScheme(const winrt::Microsoft::Terminal::TerminalControl::IControlSettings& terminalSettings) const;

        static com_ptr<ColorScheme> FromJson(const Json::Value& json);
        bool ShouldBeLayered(const Json::Value& json) const;
        void LayerJson(const Json::Value& json);

        hstring Name() const noexcept;
        com_array<uint32_t> Table() noexcept;
        uint32_t Foreground() const noexcept;
        uint32_t Background() const noexcept;
        uint32_t SelectionBackground() const noexcept;
        uint32_t CursorColor() const noexcept;

        static std::optional<std::wstring> GetNameFromJson(const Json::Value& json);

    private:
        std::wstring _schemeName;
        std::array<uint32_t, COLOR_TABLE_SIZE> _table;
        til::color _defaultForeground;
        til::color _defaultBackground;
        til::color _selectionBackground;
        til::color _cursorColor;

        friend class TerminalAppLocalTests::SettingsTests;
        friend class TerminalAppLocalTests::ColorSchemeTests;
    };
}

namespace winrt::TerminalApp::factory_implementation
{
    BASIC_FACTORY(ColorScheme);
}
