/* main.cpp --- 
 * 
 * Author: John Stark
 * Copyright (C) 2011 -John Stark, Inria.
 * Created: 
 * Version: $Id$
 * Last-Updated: 
 *           By: John Stark
 *     Update #: 0
 */

/* Commentary: 
 * Perform some tests using dtkSmartPointer with dtkAbstractData-derived objects.
 * 
 * Warning : when the instance count of a dtkAbstractObject reaches zero, it calls (this->deleteLater()).
 * This means that the object is not actually deleted until an event loop is active. 
 * 
 */

/* Change log:
 * 
 */

#include <dtkConfig.h>

#include <dtkCore/dtkAbstractData.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkGlobal.h>
#include <dtkCore/dtkLog.h>

#include <dtkCore/dtkSmartPointer.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include <QHash>

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

class TestData : public dtkAbstractData {
public:
    static QString s_TypeName;
    TestData() { }
    ~TestData() { }

    static dtkAbstractData * create() { return new  TestData(); }

    static bool registerType() {
        return dtkAbstractDataFactory::instance()->registerDataType(s_TypeName, create );
    }

};

QString TestData::s_TypeName = "TestDataType";

// /////////////////////////////////////////////////////////////////
// 
// /////////////////////////////////////////////////////////////////

#define CHECK_TEST_RESULT( cond ) CheckTestResult( cond , DTK_STRINGIZE(cond), __FILE__, __LINE__ )

inline void CheckTestResult( bool condition, const char * cond, const char * file, const int line = 0 )
{
    if ( ! condition ) {
        QString msg;
        msg = QString( "%1(%2): Test failed (%3)" ).arg(file).arg(line).arg(cond);
        throw std::runtime_error(msg.toStdString());
    }
}

int main(int argc, char* argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    int ret = DTK_FAILURE;
    try {
#if 0
        QApplication app( argc, argv );

        dtkPluginManager::instance()->setPath (argv[1]);
        dtkPluginManager::instance()->initialize();
#endif
        if  (!TestData::registerType())
            throw( std::runtime_error( "Failed to register data type" ) );

        dtkAbstractDataFactory * factory = dtkAbstractDataFactory::instance();

        dtkAbstractData * pData = factory->create( TestData::s_TypeName );
        CHECK_TEST_RESULT(pData != NULL);
        CHECK_TEST_RESULT(pData->count() == 1);

        TestData * pTestData = dynamic_cast< TestData * >( pData );
        CHECK_TEST_RESULT(pTestData != NULL);

        delete pTestData; pTestData = NULL;

        // Instantiate, test for Null.
        dtkSmartPointer< TestData > myInstance;
        CHECK_TEST_RESULT( !myInstance );  // Check cast-to-bool
        CHECK_TEST_RESULT( myInstance.isNull() );

        myInstance.take( dynamic_cast< TestData *>(factory->create( TestData::s_TypeName )) );
        CHECK_TEST_RESULT( myInstance );
        CHECK_TEST_RESULT( !myInstance.isNull() );
        CHECK_TEST_RESULT( myInstance->count() == 1 );

        TestData * notSmartPtr = myInstance;
        myInstance = NULL;
        CHECK_TEST_RESULT( !myInstance );
        CHECK_TEST_RESULT( notSmartPtr->count() == 0 );

        myInstance.take( dynamic_cast< TestData *>(factory->create( TestData::s_TypeName )) );

        {   // Scope a pointer
            // Test assignment
            dtkSmartPointer< dtkAbstractData > basePtr;
            basePtr = myInstance;
            CHECK_TEST_RESULT( !basePtr.isNull() );
            CHECK_TEST_RESULT( basePtr == myInstance );
            CHECK_TEST_RESULT( basePtr->count() == 2);
            // End of scope, count should decrease.
        }
        CHECK_TEST_RESULT( myInstance->count() == 1);

        dtkSmartPointer< TestData > myOtherInstance;
        myOtherInstance.take( dynamic_cast< TestData *>(factory->create( TestData::s_TypeName )) );

        dtkSmartPointer< TestData > myOtherInstance2;
        myOtherInstance2.take( dynamic_cast< TestData *>(factory->create( TestData::s_TypeName )) );

        
        {   // Test copy-construction
            dtkSmartPointer< TestData > copyInstance(myInstance) ;
            CHECK_TEST_RESULT( !copyInstance.isNull() );
            CHECK_TEST_RESULT( copyInstance == myInstance );
            CHECK_TEST_RESULT( copyInstance != myOtherInstance );
            CHECK_TEST_RESULT( copyInstance->count() == 2 );
        }

        // Test a set - this needs a hash function
        typedef QSet< dtkSmartPointer< dtkAbstractData > > DataSetContainer;
        DataSetContainer mySetContainer;

        // Add smartpointer instances.
        mySetContainer.insert(dtkSmartPointer< dtkAbstractData >(myInstance));
        mySetContainer.insert(dtkSmartPointer< dtkAbstractData >(myOtherInstance));
        mySetContainer.insert(dtkSmartPointer< dtkAbstractData >(myOtherInstance2));

        // Should now have 2 registered instances, 1 in this scope, 1 in container
        CHECK_TEST_RESULT( myInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 2);

        // After clearing the container the references should be cleared.
        mySetContainer.clear();
        CHECK_TEST_RESULT( myInstance->count() == 1);
        CHECK_TEST_RESULT( myOtherInstance->count() == 1);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 1);

        typedef QHash<QString, dtkSmartPointer< dtkAbstractData > > DataContainer;
        DataContainer myHashMapContainer;
        myHashMapContainer["bar"] = myInstance;
        myHashMapContainer["foo"] = myOtherInstance;
        myHashMapContainer["gee"] = myOtherInstance2;

        CHECK_TEST_RESULT( myInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 2);
        myHashMapContainer.clear();
        CHECK_TEST_RESULT( myInstance->count() == 1);
        CHECK_TEST_RESULT( myOtherInstance->count() == 1);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 1);

        // And an stl container
        typedef std::vector< dtkSmartPointer< dtkAbstractData > > StlContainer;
        StlContainer myVector;
        myVector.push_back( dtkSmartPointer< dtkAbstractData >(myInstance) );
        myVector.push_back( dtkSmartPointer< dtkAbstractData >(myOtherInstance) );
        myVector.push_back( dtkSmartPointer< dtkAbstractData >(myOtherInstance2) );
        CHECK_TEST_RESULT( myInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 2);

        // Now manipulate the vector
        myVector.resize(2);
        CHECK_TEST_RESULT( myInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 1);

        // This may cause a re-assignment of the buffer used by the vector.
        myVector.resize(10);
        CHECK_TEST_RESULT( myInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance->count() == 2);
        CHECK_TEST_RESULT( myOtherInstance2->count() == 1);

        CHECK_TEST_RESULT( myVector.at(0) == myInstance);
        CHECK_TEST_RESULT( myVector.at(1) == myOtherInstance);
        CHECK_TEST_RESULT( myVector.at(9).isNull());

        ret = DTK_SUCCEED;
    }
    catch (std::exception & e) {
        dtkDebug() << e.what();
    }
    catch (...) {
        dtkDebug() << "Caught an unknown exception" ;
    }
    if ( ret ) {
        dtkDebug() << " Test succeeded";
    } else {
        dtkDebug() << " Test failed";
    }
    return ret;
}
