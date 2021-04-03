/**
 ******************************************************************************
 * @file         	main.cpp
 * @date			03-Apr-2021, 5:01:22 PM
 * @author			nandanv
 * @brief
 ******************************************************************************
 */

//* Private Include ************************************************************************
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <gtkmm/application.h>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h> // support for loading levels from the environment variable
#include <spdlog/sinks/daily_file_sink.h>
#pragma GCC diagnostic pop

#include "MainWindow.hpp"
//* Private Constants **********************************************************************

//* Private Macros *************************************************************************

//* Private Types **************************************************************************

/**
 * Initialise spdlog
 */
void spdLog_init(void);

int main(int, char*[])
{
    spdLog_init();

    spdlog::info("Starting...");

    auto app = Gtk::Application::create("org.gtkmm.button");
    CMainWindow oMainWindow;

    app->run(oMainWindow);

    spdlog::shutdown();
    return 0;
}

//+-------------------------------------------------------------------------------- Method -
//|Author               : nandanv
//|Created On           : 03-Apr-2021, 9:37:54 PM
//|Description          : <see declaration>
//+-----------------------------------------------------------------------------------------
void spdLog_init(void)
{
    auto consoleLogger = std::make_shared <
        spdlog::sinks::ansicolor_stdout_sink_mt>();

    // Roll over every day at 23:59:00
    auto fileSink =
        std::make_shared <spdlog::sinks::daily_file_sink_mt>("logs/daily.txt",
                                                             23,
                                                             59);

    spdlog::logger logger("log",
                              {
                              consoleLogger,
                              fileSink
                              });


    logger.info("spdlog version {}.{}.{}",
                SPDLOG_VER_MAJOR,
                SPDLOG_VER_MINOR,
                SPDLOG_VER_PATCH);

    spdlog::set_default_logger(std::make_shared <spdlog::logger>("log",
                                                                 spdlog::sinks_init_list(
                                                                     {
                                                                         consoleLogger,
                                                                         fileSink
                                                                     })));

    /* Log levels at startup
     * The environment variable SPDLOG_LEVEL can be used to modify the log level
     */
    spdlog::cfg::load_env_levels();
}
