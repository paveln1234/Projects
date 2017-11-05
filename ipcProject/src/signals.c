#define _POSIX_C_SOURCE 2
#define _XOPEN_SOURCE 500

#include "sigHandler.h"
#include "reporter.h"
#include "opDB.h"
#include "subDB.h"
#include <signal.h>
#include <stdio.h>
#include "operator.h"
#include "reporter.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct SigHandler
{
	sigset_t m_userSignals;
};

static void* ActOnSignal(void* _sigHandler);

SignalResult CreateSigHandler(SigHandler** _sigHandler, Reporter* _reporter)
{
	pthread_t tid;
	
	SigHandler* sigHandler = malloc(sizeof(SigHandler));
	if(sigHandler == NULL)
	{
		return SIGNAL_ALLOCATION_FAIL;
	}
	
	sigemptyset(&sigHandler->m_userSignals);
	sigaddset(&sigHandler->m_userSignals, SIGUSR1);
	sigaddset(&sigHandler->m_userSignals, SIGUSR2);
	pthread_sigmask(SIG_BLOCK, &sigHandler->m_userSignals, NULL);
	
	pthread_create(&tid, NULL, ActOnSignal, sigHandler);
	return REPORTER_SUCCESS;
}

static void* ActOnSignal(void* _sigHandler)
{
	int sigReceived;
	SigHandler* sigHandler = (SigHandler*)_sigHandler;
	while(1)
	{
		printf("reporting waiting for signal...\n");
		sigwait(&sigHandler->m_userSignals, &sigReceived);
		printf("sigwait passed\n");
		if(sigReceived == SIGUSR1)
		{
			printf("received SIGUSR1\n");
		}
		else if(sigReceived == SIGUSR2)
		{
			printf("received SIGUSR2");
		}
	}
	return NULL;
}
