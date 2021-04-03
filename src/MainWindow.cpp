/**
 ******************************************************************************
 * @file         	MainWindow.cpp
 * @date			03-Apr-2021, 6:59:31 PM
 * @author			nandanv		
 * @brief        
 ******************************************************************************
 */

//* Private Include ************************************************************************
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <spdlog/spdlog.h>

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

    m_ConnectButton.set_vexpand(true);
    m_ConnectButton.set_hexpand(true);
    m_AbortButton.set_vexpand(true);
    m_AbortButton.set_hexpand(true);
    m_isConnected.set_vexpand(true);
    m_isConnected.set_hexpand(true);

    m_ConnectButton.signal_clicked().connect(sigc::mem_fun(*this,
                                                           &CMainWindow::connectButton_clicked));

    m_AbortButton.signal_clicked().connect(sigc::mem_fun(*this,
                                                         &CMainWindow::abortButton_clicked));

    m_MainGrid.add(m_ScrolledWindow);
    m_MainGrid.add(m_ConnectButton);
    m_MainGrid.add(m_AbortButton);
    m_MainGrid.add(m_isConnected);

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
    spdlog::info("Connect button clicked");

    if (true
        == m_isConnected.get_active())
    {
        m_ConnectButton.set_label("Connect");
        m_refTextBuffer->set_text("Connect clicked");
        m_isConnected.set_active(false);
        return;
    }

    m_ConnectButton.set_label("Disconnect");
    m_refTextBuffer->set_text("Disconnect clicked");
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
