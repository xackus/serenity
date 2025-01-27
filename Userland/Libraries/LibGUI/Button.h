/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/Function.h>
#include <LibGUI/AbstractButton.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/StylePainter.h>
#include <LibGfx/TextAlignment.h>

namespace GUI {

class Button : public AbstractButton {
    C_OBJECT(Button);

public:
    virtual ~Button() override;

    void set_icon(RefPtr<Gfx::Bitmap>&&);
    const Gfx::Bitmap* icon() const { return m_icon.ptr(); }
    Gfx::Bitmap* icon() { return m_icon.ptr(); }

    void set_text_alignment(Gfx::TextAlignment text_alignment) { m_text_alignment = text_alignment; }
    Gfx::TextAlignment text_alignment() const { return m_text_alignment; }

    Function<void(unsigned modifiers)> on_click;
    Function<void(const ContextMenuEvent&)> on_context_menu_request;

    void set_button_style(Gfx::ButtonStyle style) { m_button_style = style; }
    Gfx::ButtonStyle button_style() const { return m_button_style; }

    virtual void click(unsigned modifiers = 0) override;
    virtual void context_menu_event(ContextMenuEvent&) override;

    Action* action() { return m_action; }
    Action const* action() const { return m_action; }
    void set_action(Action&);

    virtual bool is_uncheckable() const override;

    int icon_spacing() const { return m_icon_spacing; }
    void set_icon_spacing(int spacing) { m_icon_spacing = spacing; }

    void set_menu(RefPtr<GUI::Menu>);

protected:
    explicit Button(String text = {});
    virtual void mousedown_event(MouseEvent&) override;
    virtual void paint_event(PaintEvent&) override;

private:
    RefPtr<Gfx::Bitmap> m_icon;
    RefPtr<GUI::Menu> m_menu;
    Gfx::ButtonStyle m_button_style { Gfx::ButtonStyle::Normal };
    Gfx::TextAlignment m_text_alignment { Gfx::TextAlignment::Center };
    WeakPtr<Action> m_action;
    int m_icon_spacing { 4 };
};

}
