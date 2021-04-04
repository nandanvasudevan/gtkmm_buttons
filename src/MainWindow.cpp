/**
 ******************************************************************************
 * @file         	MainWindow.cpp
 * @date			03-Apr-2021, 6:59:31 PM
 * @author			nandanv		
 * @brief        
 ******************************************************************************
 */

//* Private Include ************************************************************************
#define SPDLOG_COMPILED_LIB

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <glibmm/main.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <spdlog/spdlog.h>
#pragma GCC diagnostic pop

#include "MainWindow.hpp"
//* Private Constants **********************************************************************

//* Private Macros *************************************************************************

//* Private Types **************************************************************************

//+-------------------------------------------------------------------------------- Method -
//|Author               : nandanv
//|Created On           : 03-Apr-2021, 7:12:29 PM
//|Description          : <see declaration>
//+-----------------------------------------------------------------------------------------
CMainWindow::CMainWindow() :
    m_ConnectButton("Connect"),
    m_AbortButton("Abort"),
    m_isConnected("Is connected")
{
    set_title("Buttons");

    add(m_MainGrid);

    m_TextView.set_editable(false);
    m_refTextBuffer = Gtk::TextBuffer::create();

    m_isConnected.set_sensitive(false);

    m_ScrolledWindow.add(m_TextView);

    m_AbortButton.set_vexpand(false);
    m_ConnectButton.set_vexpand(false);
    m_isConnected.set_vexpand(false);
    m_Progressbar.set_vexpand(false);
    m_TextView.set_vexpand(false);

    m_AbortButton.set_hexpand(true);
    m_ConnectButton.set_hexpand(true);
    m_isConnected.set_hexpand(true);
    m_Progressbar.set_hexpand(true);
    m_TextView.set_hexpand(true);

    m_ConnectButton.signal_clicked().connect(sigc::mem_fun(*this,
                                                           &CMainWindow::connectButton_clicked));

    m_AbortButton.signal_clicked().connect(sigc::mem_fun(*this,
                                                         &CMainWindow::abortButton_clicked));

    auto timeout =
        Glib::signal_timeout().connect(sigc::mem_fun(*this,
                                                     &CMainWindow::updateProgressbar),
                                       PROGRESS_UPDATE_TIME_ms);

    m_MainGrid.attach(m_ConnectButton,
                      0,
                      0,
                      400);
    m_MainGrid.add(m_AbortButton);
    m_MainGrid.add(m_isConnected);
    m_MainGrid.attach(m_ScrolledWindow,
                      1,
                      1,
                      1000);
    m_MainGrid.attach(m_Progressbar,
                      1,
                      2,
                      1000,
                      250);
    m_MainGrid.attach(m_PulseBar,
                      1,
                      3,
                      1000,
                      300);
    m_MainGrid.attach(m_spinner,
                      1,
                      4,
                      500,
                      500);

    m_Progressbar.set_halign(Gtk::ALIGN_CENTER);
    m_Progressbar.set_valign(Gtk::ALIGN_CENTER);
    m_PulseBar.set_halign(Gtk::ALIGN_CENTER);
    m_PulseBar.set_valign(Gtk::ALIGN_CENTER);

    show_all_children();
}

CMainWindow::~CMainWindow()
{
    // TODO Auto-generated destructor stub
}

//+-------------------------------------------------------------------------------- Method -
//|Author               : nandanv
//|Created On           : 03-Apr-2021, 7:12:33 PM
//|Description          : <see declaration>
//+-----------------------------------------------------------------------------------------
void CMainWindow::connectButton_clicked(void)
{
    if (true
        == m_isConnected.get_active())
    {
        m_spinner.stop();
        m_ConnectButton.set_label("Connect");
        m_refTextBuffer->set_text("Disconnect clicked");
        spdlog::info("Disconnect button clicked");
        m_isConnected.set_active(false);
        m_TextView.set_buffer(m_refTextBuffer);
        return;
    }

    m_spinner.start();
    spdlog::info("Connect button clicked");
    m_refTextBuffer->set_text("Connect clicked");
    m_ConnectButton.set_label("Disconnect");
    m_isConnected.set_active(true);
    m_TextView.set_buffer(m_refTextBuffer);
}

//+-------------------------------------------------------------------------------- Method -
//|Author               : nandanv
//|Created On           : 03-Apr-2021, 7:47:27 PM
//|Description          : <see declaration>
//+-----------------------------------------------------------------------------------------
void CMainWindow::abortButton_clicked(void)
{
    spdlog::info("Aborting...");
    hide();
}

//+-------------------------------------------------------------------------------- Method -
//|Author               : nandanv
//|Created On           : 04-Apr-2021, 12:07:28 AM
//|Description          : <see declaration>
//+-----------------------------------------------------------------------------------------
bool CMainWindow::updateProgressbar(void)
{
    static double dProgress = 0;
    static uint16_t uiCounter = 0;
    static constexpr uint16_t PULSE_PRESCALE_COUNTER = 7;
    static constexpr uint8_t PROGRESS_BAR_PRECISION = 2;

    if (uiCounter++
        > PULSE_PRESCALE_COUNTER)
    {
        uiCounter = 0;
        m_PulseBar.pulse();
    }

    if (dProgress
        > 1)
    {
        return true;
    }

    if (false
        == m_isConnected.get_active())
    {
        return true;
    }

    dProgress += (double)PROGRESS_UPDATE_FRACTION;

    m_Progressbar.set_fraction(dProgress);

    spdlog::trace("Updating progress bar: {:.{}f}%",
                  dProgress
                  * 100,
                  PROGRESS_BAR_PRECISION);
    return true;
}
