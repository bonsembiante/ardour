// -*- c++ -*-
// Generated by gmmproc 2.45.3 -- DO NOT MODIFY!
#ifndef _GTKMM_FONTSELECTION_H
#define _GTKMM_FONTSELECTION_H


#include <glibmm/ustring.h>
#include <sigc++/sigc++.h>

/* $Id: fontselection.hg,v 1.2 2003/01/22 23:04:19 murrayc Exp $ */

/* Copyright (C) 1998-2002 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include <gtkmm/box.h>
#include <gtkmm/dialog.h>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkFontSelection GtkFontSelection;
typedef struct _GtkFontSelectionClass GtkFontSelectionClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class FontSelection_Class; } // namespace Gtk
#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GtkFontSelectionDialog GtkFontSelectionDialog;
typedef struct _GtkFontSelectionDialogClass GtkFontSelectionDialogClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gtk
{ class FontSelectionDialog_Class; } // namespace Gtk
namespace Gtk
{

class Button;
class Entry;
class TreeView;
class RadioButton;


/** A widget for selecting fonts.
 *
 * The Gtk::FontSelection widget lists the available fonts, styles and
 * sizes, allowing the user to select a font. It is used in the
 * Gtk::FontSelectionDialog widget to provide a dialog box for selecting
 * fonts.
 *
 * @ingroup Widgets
 */

class FontSelection : public VBox
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef FontSelection CppObjectType;
  typedef FontSelection_Class CppClassType;
  typedef GtkFontSelection BaseObjectType;
  typedef GtkFontSelectionClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~FontSelection();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class FontSelection_Class;
  static CppClassType fontselection_class_;

  // noncopyable
  FontSelection(const FontSelection&);
  FontSelection& operator=(const FontSelection&);

protected:
  explicit FontSelection(const Glib::ConstructParams& construct_params);
  explicit FontSelection(GtkFontSelection* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkFontSelection*       gobj()       { return reinterpret_cast<GtkFontSelection*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkFontSelection* gobj() const { return reinterpret_cast<GtkFontSelection*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

   //deprecated
public:
  FontSelection();

  
  /** This returns the Gtk::TreeView that lists font families, for
   * example, 'Sans', 'Serif', etc.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  TreeView* get_family_list();
  
  /** This returns the Gtk::TreeView that lists font families, for
   * example, 'Sans', 'Serif', etc.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  const TreeView* get_family_list() const;

  
  /** This returns the Gtk::TreeView which lists all styles available for
   * the selected font. For example, 'Regular', 'Bold', etc.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  TreeView* get_face_list();
  
  /** This returns the Gtk::TreeView which lists all styles available for
   * the selected font. For example, 'Regular', 'Bold', etc.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  const TreeView* get_face_list() const;

  
  /** This returns the Gtk::Entry used to allow the user to edit the font
   * number manually instead of selecting it from the list of font sizes.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  Entry* get_size_entry();
  
  /** This returns the Gtk::Entry used to allow the user to edit the font
   * number manually instead of selecting it from the list of font sizes.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  const Entry* get_size_entry() const;

  
  /** This returns the Gtk::TreeeView used to list font sizes.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  TreeView* get_size_list();
  
  /** This returns the Gtk::TreeeView used to list font sizes.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  const TreeView* get_size_list() const;

  
  /** This returns the Gtk::Entry used to display the font as a preview.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  Entry* get_preview_entry();
  
  /** This returns the Gtk::Entry used to display the font as a preview.
   * 
   * @return A Gtk::Widget that is part of @a fontsel.
   */
  const Entry* get_preview_entry() const;

  
  /** Gets the Pango::FontFamily representing the selected font family.
   * 
   * @return A Pango::FontFamily representing the
   * selected font family. Font families are a collection of font
   * faces. The returned object is owned by @a fontsel and must not
   * be modified or freed.
   */
  Glib::RefPtr<Pango::FontFamily> get_family();
  
  /** Gets the Pango::FontFamily representing the selected font family.
   * 
   * @return A Pango::FontFamily representing the
   * selected font family. Font families are a collection of font
   * faces. The returned object is owned by @a fontsel and must not
   * be modified or freed.
   */
  Glib::RefPtr<const Pango::FontFamily> get_family() const;

  
  /** Gets the Pango::FontFace representing the selected font group
   * details (i.e.\ family, slant, weight, width, etc).
   * 
   * @return A Pango::FontFace representing the
   * selected font group details. The returned object is owned by
   *  @a fontsel and must not be modified or freed.
   */
  Glib::RefPtr<Pango::FontFace> get_face();
  
  /** Gets the Pango::FontFace representing the selected font group
   * details (i.e.\ family, slant, weight, width, etc).
   * 
   * @return A Pango::FontFace representing the
   * selected font group details. The returned object is owned by
   *  @a fontsel and must not be modified or freed.
   */
  Glib::RefPtr<const Pango::FontFace> get_face() const;

  
  /** The selected font size.
   * 
   * @return A n integer representing the selected font size,
   * or -1 if no font size is selected.
   */
  int get_size() const;

  
  /** Gets the currently-selected font name. 
   * 
   * Note that this can be a different string than what you set with 
   * set_font_name(), as the font selection widget may 
   * normalize font names and thus return a string with a different structure. 
   * For example, "Helvetica Italic Bold 12" could be normalized to 
   * "Helvetica Bold Italic 12". Use pango_font_description_equal()
   * if you want to compare two font descriptions.
   * 
   * @return A string with the name of the current font, or <tt>0</tt> if 
   * no font is selected. You must free this string with Glib::free().
   */
  Glib::ustring get_font_name() const;
  
  /** Sets the currently-selected font. 
   * 
   * Note that the @a fontsel needs to know the screen in which it will appear 
   * for this to work; this can be guaranteed by simply making sure that the 
   *  @a fontsel is inserted in a toplevel window before you call this function.
   * 
   * @param fontname A font name like "Helvetica 12" or "Times Bold 18".
   * @return <tt>true</tt> if the font could be set successfully; <tt>false</tt> if no 
   * such font exists or if the @a fontsel doesn't belong to a particular 
   * screen yet.
   */
  bool set_font_name(const Glib::ustring& fontname);
  
  /** Gets the text displayed in the preview area.
   * 
   * @return The text displayed in the preview area. 
   * This string is owned by the widget and should not be 
   * modified or freed.
   */
  Glib::ustring get_preview_text() const;
  
  /** Sets the text displayed in the preview area.
   * The @a text is used to show how the selected font looks.
   * 
   * @param text The text to display in the preview area.
   */
  void set_preview_text(const Glib::ustring& text);

  //TODO: Remove these accessors when we can break ABI.
  //They probably all return null now anyway.


#ifndef GTKMM_DISABLE_DEPRECATED

  /** @deprecated You should not need to call this method.
   */
   Entry* get_font_entry();
  const Entry* get_font_entry() const;
 
  /** @deprecated You should not need to call this method.
   */
   Entry* get_font_style_entry();
  const Entry* get_font_style_entry() const;
 
  /** @deprecated You should not need to call this method.
   */
   RadioButton* get_pixels_button();
  const RadioButton* get_pixels_button() const;
 
  /** @deprecated You should not need to call this method.
   */
   RadioButton* get_points_button();
  const RadioButton* get_points_button() const;
 
  /** @deprecated You should not need to call this method.
   */
   Button* get_filter_button();
  const Button* get_filter_button() const;
 #endif // GTKMM_DISABLE_DEPRECATED


  //Note: The GdkFont "font" property is deprecated, or should be.
  /** The string that represents this font.
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_font_name() ;

/** The string that represents this font.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_font_name() const;

  /** The text to display in order to demonstrate the selected font.
   *
   * @return A PropertyProxy that allows you to get or set the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy< Glib::ustring > property_preview_text() ;

/** The text to display in order to demonstrate the selected font.
   *
   * @return A PropertyProxy_ReadOnly that allows you to get the value of the property,
   * or receive notification when the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly< Glib::ustring > property_preview_text() const;


};

/** A dialog box for selecting fonts.
 *
 * The Gtk::FontSelectionDialog widget is a dialog box for selecting a font.
 *
 * @ingroup Dialogs
 */

class FontSelectionDialog : public Dialog
{
  public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef FontSelectionDialog CppObjectType;
  typedef FontSelectionDialog_Class CppClassType;
  typedef GtkFontSelectionDialog BaseObjectType;
  typedef GtkFontSelectionDialogClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  virtual ~FontSelectionDialog();

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:
  friend class FontSelectionDialog_Class;
  static CppClassType fontselectiondialog_class_;

  // noncopyable
  FontSelectionDialog(const FontSelectionDialog&);
  FontSelectionDialog& operator=(const FontSelectionDialog&);

protected:
  explicit FontSelectionDialog(const Glib::ConstructParams& construct_params);
  explicit FontSelectionDialog(GtkFontSelectionDialog* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;


  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GtkObject.
  GtkFontSelectionDialog*       gobj()       { return reinterpret_cast<GtkFontSelectionDialog*>(gobject_); }

  ///Provides access to the underlying C GtkObject.
  const GtkFontSelectionDialog* gobj() const { return reinterpret_cast<GtkFontSelectionDialog*>(gobject_); }


public:
  //C++ methods used to invoke GTK+ virtual functions:

protected:
  //GTK+ Virtual Functions (override these to change behaviour):

  //Default Signal Handlers::


private:

  
public:

  FontSelectionDialog();
    explicit FontSelectionDialog(const Glib::ustring& title);


  /** Sets the currently selected font.
   * 
   * @param fontname A font name like "Helvetica 12" or "Times Bold 18".
   * @return <tt>true</tt> if the font selected in @a fsd is now the
   *  @a fontname specified, <tt>false</tt> otherwise.
   */
  bool set_font_name(const Glib::ustring& fontname);
  
  /** Gets the currently-selected font name.
   * 
   * Note that this can be a different string than what you set with 
   * set_font_name(), as the font selection widget
   * may normalize font names and thus return a string with a different 
   * structure. For example, "Helvetica Italic Bold 12" could be normalized 
   * to "Helvetica Bold Italic 12".  Use pango_font_description_equal()
   * if you want to compare two font descriptions.
   * 
   * @return A string with the name of the current font, or <tt>0</tt> if no 
   * font is selected. You must free this string with Glib::free().
   */
  Glib::ustring get_font_name() const;
  
  /** Gets the text displayed in the preview area.
   * 
   * @return The text displayed in the preview area. 
   * This string is owned by the widget and should not be 
   * modified or freed.
   */
  Glib::ustring get_preview_text() const;
  
  /** Sets the text displayed in the preview area.
   * 
   * @param text The text to display in the preview area.
   */
  void set_preview_text(const Glib::ustring& text);

  
  /** Gets the 'OK' button.
   * 
   * @return The Gtk::Widget used in the dialog
   * for the 'OK' button.
   */
  Button* get_ok_button();
  
  /** Gets the 'OK' button.
   * 
   * @return The Gtk::Widget used in the dialog
   * for the 'OK' button.
   */
  const Button* get_ok_button() const;

  
  /** Gets the 'Cancel' button.
   * 
   * @return The Gtk::Widget used in the dialog
   * for the 'Cancel' button.
   */
  Button* get_cancel_button();
  
  /** Gets the 'Cancel' button.
   * 
   * @return The Gtk::Widget used in the dialog
   * for the 'Cancel' button.
   */
  const Button* get_cancel_button() const;

  
  /** Obtains a button. The button doesn't have any function.
   * 
   * Deprecated: 2.16: Don't use this function.
   * 
   * @return A Gtk::Widget.
   */
  Button* get_apply_button();
  
  /** Obtains a button. The button doesn't have any function.
   * 
   * Deprecated: 2.16: Don't use this function.
   * 
   * @return A Gtk::Widget.
   */
  const Button* get_apply_button() const;


};

} // namespace Gtk


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::FontSelection
   */
  Gtk::FontSelection* wrap(GtkFontSelection* object, bool take_copy = false);
} //namespace Glib


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gtk::FontSelectionDialog
   */
  Gtk::FontSelectionDialog* wrap(GtkFontSelectionDialog* object, bool take_copy = false);
} //namespace Glib


#endif /* _GTKMM_FONTSELECTION_H */

