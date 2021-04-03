/**
 ******************************************************************************
 * @file         	MainWindow.hpp
 * @date			03-Apr-2021, 6:59:31 PM
 * @author			nandanv
 * @brief          
 ******************************************************************************
 */

#ifndef SRC_MAINWINDOW_HPP_
#define SRC_MAINWINDOW_HPP_
//* Public Include *************************************************************************
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/grid.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textview.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/window.h>
//* Public Constants ***********************************************************************

//* Public Macros **************************************************************************

//* Public Types ***************************************************************************

class CMainWindow : public Gtk::Window
{
public:
    CMainWindow();
    virtual ~CMainWindow();

protected:
    void connectButton_clicked(void);
    void abortButton_clicked(void);

private:
    Gtk::Button m_ConnectButton;
    Gtk::Button m_AbortButton;

    Gtk::CheckButton m_isConnected;

    Gtk::Grid m_MainGrid;

    Gtk::TextView m_TextView;

    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

    Gtk::ScrolledWindow m_ScrolledWindow;
};

#endif /* SRC_MAINWINDOW_HPP_ */
