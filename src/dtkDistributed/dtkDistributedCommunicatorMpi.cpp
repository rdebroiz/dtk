/* dtkCommunicatorMpi.cpp --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Feb 15 16:51:02 2010 (+0100)
 * Version: $Id$
 * Last-Updated: Fri Sep  9 13:03:09 2011 (+0200)
 *           By: jwintz
 *     Update #: 132
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#include "dtkDistributedCommunicatorMpi.h"

#include <mpi.h>

// /////////////////////////////////////////////////////////////////
// Helper functions
// /////////////////////////////////////////////////////////////////

MPI::Datatype data_type(dtkDistributedCommunicator::DataType type)
{
    switch(type) {
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBool:   return MPI::BOOL;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorChar:   return MPI::CHAR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorInt:    return MPI::INT;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLong:   return MPI::LONG;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorFloat:  return MPI::FLOAT;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorDouble: return MPI::DOUBLE;
    default:
        qDebug() << "dtkCommunicatorMpi: data type not handled.";
        return MPI::BYTE;
    }
}

MPI::Op operation_type(dtkDistributedCommunicator::OperationType type)
{
    switch(type) {
    case dtkDistributedCommunicator::dtkDistributedCommunicatorMin:        return MPI::MIN;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorMax:        return MPI::MAX;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorSum:        return MPI::SUM;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorProduct:    return MPI::PROD;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBitwiseAnd: return MPI::BAND;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBitwiseOr:  return MPI::BOR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorBitwiseXor: return MPI::BXOR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLogicalAnd: return MPI::LAND;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLogicalOr:  return MPI::LOR;
    case dtkDistributedCommunicator::dtkDistributedCommunicatorLogicalXor: return MPI::LXOR;
    default:
        qDebug() << "dtkCommunicatorMpi: operation type not handled.";
        return MPI::MIN;
    }
}

// /////////////////////////////////////////////////////////////////
// dtkCommunicatorMpi
// /////////////////////////////////////////////////////////////////

class dtkDistributedCommunicatorMpiPrivate
{
public:
    
};

dtkDistributedCommunicatorMpi::dtkDistributedCommunicatorMpi(void) : dtkDistributedCommunicator(), d(new dtkDistributedCommunicatorMpiPrivate)
{

}

dtkDistributedCommunicatorMpi::~dtkDistributedCommunicatorMpi(void)
{
    delete d;

    d = NULL;
}

//! Mpi communicator initializer.
/*! 
 *  Initializes the MPI execution environment. This function must be
 *  called in every MPI program, must be called before any other MPI
 *  functions and must be called only once in an MPI program.
 * 
 *  \code
 *  dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
 *  communicator->initialize();
 *  ...
 *  ...
 *  communicator->uninitialize();
 *  \endcode
 *
 * \sa uninitialize.
 */

void dtkDistributedCommunicatorMpi::initialize(void)
{
    int    argc = qApp->argc(); // These methods are obsolete but should be really exist in QCoreApplication
    char **argv = qApp->argv(); // These methods are obsolete but should be really exist in QCoreApplication

    MPI::Init(argc, argv);
}

//! Mpi communicator uninitializer.
/*! 
 *  Terminates the MPI execution environment. This function should be
 *  the last MPI routine called in every MPI program - no other MPI
 *  routines may be called after it.
 *
 *  \code
 *  dtkDistributedCommunicator *communicator = new dtkDistributedCommunicatorMpi;
 *  communicator->initialize();
 *  ...
 *  ...
 *  communicator->uninitialize();
 *  \endcode
 *
 * \sa initialize.
 */

void dtkDistributedCommunicatorMpi::uninitialize(void)
{
    MPI::Finalize();
}

//! 
/*! 
 *  Returns an elapsed wall clock time in seconds (double precision)
 *  on the calling processor.
 *
 *  \sa tick.
 */

double dtkDistributedCommunicatorMpi::time(void)
{
    return MPI::Wtime();
}

//! 
/*! 
 *  Returns the resolution in seconds (double precision) of time().
 * 
 *  \sa time.
 */

double dtkDistributedCommunicatorMpi::tick(void)
{
    return MPI::Wtick();
}

//! 
/*! 
 *  Determines the rank of the calling process within the
 *  communicator. Initially, each process will be assigned a unique
 *  integer rank between 0 and number of processors - 1 within the
 *  communicator.
 *
 *  \sa size.
 */

int dtkDistributedCommunicatorMpi::rank(void)
{
    return MPI::COMM_WORLD.Get_rank();
}

//!  
/*! 
 *  Determines the number of processes in the group associated with a
 *  communicator.
 *
 *  \sa rank.
 */

int dtkDistributedCommunicatorMpi::size(void)
{
    return MPI::COMM_WORLD.Get_size();
}

//! 
/*! 
 *  Returns the name of the processor.
 */

QString dtkDistributedCommunicatorMpi::name(void) const
{
    int len; char name[MPI_MAX_PROCESSOR_NAME];

    memset(name,0,MPI_MAX_PROCESSOR_NAME);
    MPI::Get_processor_name(name,len);
    memset(name+len,0,MPI_MAX_PROCESSOR_NAME-len);

    return QString(name);
}

//! Standard-mode, blocking send.
/*! 
 *  Basic blocking send operation. Routine returns only after the
 *  application buffer in the sending task is free for reuse.
 */

void dtkDistributedCommunicatorMpi::send(void *data, quint16 size, DataType dataType, quint16 target, int tag)
{
    MPI::COMM_WORLD.Send(data, size, data_type(dataType), target, tag);
}

//! Standard-mode, blocking receive.
/*! 
 *  Receive a message and block until the requested data is available
 *  in the application buffer in the receiving task.
 */

void dtkDistributedCommunicatorMpi::receive(void *data, quint16 size, DataType dataType, quint16 source, int tag)
{
    MPI::COMM_WORLD.Recv(data, size, data_type(dataType), source, tag);
}

void dtkDistributedCommunicatorMpi::receive(void *data, quint16 size, DataType dataType, quint16 source, int tag, int& from)
{
    MPI::Status status;
    MPI::COMM_WORLD.Recv(data, size, data_type(dataType), source, tag, status);
    from = status.Get_source();
}

//! Barrier.
/*!
 *  Creates a barrier synchronization. Each task, when reaching the
 *  barrier call, blocks until all tasks in the group reach the same
 *  barrier call.
 */

void dtkDistributedCommunicatorMpi::barrier(void)
{
    MPI::COMM_WORLD.Barrier();
}

//! Broadcast.
/*! 
 *  Broadcasts (sends) a message from the process with rank "source"
 *  to all other processes in the group.
 */

void dtkDistributedCommunicatorMpi::broadcast(void *data, quint16 size, DataType dataType, quint16 source)
{
    MPI::COMM_WORLD.Bcast(data, size, data_type(dataType), source); 
}

//! Gather.
/*! 
 *  Gathers distinct messages from each task in the group to a single
 *  destination task. This routine is the reverse operation of
 *  scatter. If all is true, target is not taken into account.
 *
 *  \sa scatter.
 */

void dtkDistributedCommunicatorMpi::gather(void *send, void *recv, quint16 size, DataType dataType, quint16 target, bool all)
{
    if(all)
        MPI::COMM_WORLD.Allgather(send, size, data_type(dataType), recv, size, data_type(dataType));
    else
        MPI::COMM_WORLD.Gather(send, size, data_type(dataType), recv, size, data_type(dataType), target);
}

//! Scatter.
/*! 
 *  Distributes distinct messages from a single source task to each
 *  task in the group.
 *
 *  \sa gather.
 */

void dtkDistributedCommunicatorMpi::scatter(void *send, void *recv, quint16 size, DataType dataType, quint16 source)
{
    MPI::COMM_WORLD.Scatter(send, size, data_type(dataType), recv, size, data_type(dataType), source);
}

//! Reduce.
/*! 
 *  Applies a reduction operation on all tasks in the group and places
 *  the result in one task. If all is true, target is not taken into
 *  account.
 *
 *  \sa dtkDistributedCommunicator::OperationType.
 */

void dtkDistributedCommunicatorMpi::reduce(void *send, void *recv, quint16 size, DataType dataType, OperationType operationType, quint16 target, bool all)
{
    if(all)
        MPI::COMM_WORLD.Allreduce(send, recv, size, data_type(dataType), operation_type(operationType));
    else
        MPI::COMM_WORLD.Reduce(send, recv, size, data_type(dataType), operation_type(operationType), target);
}

// /////////////////////////////////////////////////////////////////
// Documentation
// /////////////////////////////////////////////////////////////////

//! \class dtkDistributedCommunicatorMpi
/*! 
 *  \brief A mpi based dtk communicator.
 */
