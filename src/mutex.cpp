#include <csignal>

#include "app.hpp"
#include "logger.hpp"
#include "mutex.hpp"

int SIG_DELAY = 100;

MutexStore::MutexStore(die_handler_func die_handler) {

	logger::debug << app::name << ": registering signal handlers" << std::endl;

	struct sigaction exit_action, ignore_action;

	exit_action.sa_handler = die_handler;
	sigemptyset(&exit_action.sa_mask);
	exit_action.sa_flags = 0;

	ignore_action.sa_handler = SIG_IGN;
	sigemptyset(&ignore_action.sa_mask);
	ignore_action.sa_flags = 0;

	sigaction(SIGTERM, &exit_action, NULL);
	sigaction(SIGALRM, &ignore_action, NULL);
	sigaction(SIGHUP, &ignore_action, NULL);
	sigaction(SIGINT, &exit_action, NULL);
	sigaction(SIGPIPE, &ignore_action, NULL);
	sigaction(SIGQUIT, &ignore_action, NULL);
	sigaction(SIGUSR1, &ignore_action, NULL);
	sigaction(SIGUSR2, &ignore_action, NULL);
}
