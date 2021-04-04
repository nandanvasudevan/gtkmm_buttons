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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/grid.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textview.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinner.h>
#include <gtkmm/window.h>
#pragma GCC diagnostic pop
//* Public Constants ***********************************************************************

//* Public Macros **************************************************************************

//* Public Types ***************************************************************************

class CMainWindow : public Gtk::Window
{
public:
    CMainWindow();
    virtual ~CMainWindow();

protected:

    //! Handles click events for the connect/disconnect button
    void connectButton_clicked(void);

    //! Handles click events for the abort button
    void abortButton_clicked(void);

private:
    //! The amount by which the progress bar should be updated
    constexpr static float PROGRESS_UPDATE_FRACTION = 0.001f;

    //! The interval at which the progress bars should be updated
    constexpr static uint16_t PROGRESS_UPDATE_TIME_ms = 10;

    Gtk::Button m_ConnectButton;
    Gtk::Button m_AbortButton;

    Gtk::CheckButton m_isConnected;

    Gtk::Grid m_MainGrid;

    Gtk::ProgressBar m_Progressbar;
    Gtk::ProgressBar m_PulseBar;

    Gtk::ScrolledWindow m_ScrolledWindow;

    Gtk::Spinner m_spinner;

    Gtk::TextView m_TextView;

    Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
};

#endif /* SRC_MAINWINDOW_HPP_ */
