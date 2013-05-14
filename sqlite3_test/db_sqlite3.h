// Copyright (c) 2011, NetEase Inc. All rights reserved.
//
// Author: Wang Rongtao (rtwang@corp.netease.com)
// Date: 2010/5/18
//
// SQLite Database

#ifndef DB_DB_SQLITE3_H_
#define DB_DB_SQLITE3_H_

#include "third_party/sqlite3/sqlite3.h"
#include <stdint.h>
#include <string>

namespace ndb
{
    
    typedef int (*SQLiteQueryDelegate)(void*, int, char**, char**);
    
    class SQLiteDB;
    
    /*
     *  Purpose     Query result class
     */
    class SQLiteResultTable
    {
        friend class SQLiteDB;
        
    public:
        
        SQLiteResultTable();
        SQLiteResultTable(SQLiteResultTable& src);
        virtual ~SQLiteResultTable();
        
        SQLiteResultTable& operator=(SQLiteResultTable& src);
        
        int         GetRowCount() const;
        int         GetColumnCount() const;
        
        const char* GetValue(int row, int col) const;
        const char** const operator[](int row) const;
        
        const char* GetColumnName(int col) const;
        
        bool        IsEmpty() const;
        void        Free();
        
    private:
        
        void        Reset();
        
        int         row_;
        int         col_;
        char**      result_column_;
        char**      result_;
    };
    
    
    /*
     *  Purpose     Query statement class
     */
    
    class SQLiteStatement
    {
        friend class SQLiteDB;
        
    public:
        
        SQLiteStatement();
        SQLiteStatement(SQLiteStatement& src);
        virtual ~SQLiteStatement();
        
        SQLiteStatement& operator=(SQLiteStatement& src);
        
        int Finalize();
        
    public:
        
        /*
         *  Purpose     Before the first result
         */
        int             Rewind();
        
        /*
         *  Purpose     Execute SQL  command and return the next row result
         *  Return      SQLITE_DONE  means execute finish, you should reset the statement before execute again.
         *              SQLITE_ROW   means return row result, you can get value by statement method.
         *              SQLITE_ERROR something wrong
         *              SQLITE_BUSY  db is busy, if it happend on update operation you should redo the sql command or rollback.
         */
        int             NextRow();
        
        /*
         *  Purpose     Check the record is at the end or not.
         */
        bool            IsEof();
        
        /*
         *  Purpose     Get data from column(http://www.sqlite.org/c3ref/column_blob.html)
         */
        bool            IsNullField(int col);
        const void*     GetBlobField(int col);
        int             GetBytesField(int col);
        int             GetBytes16Field(int col);
        double          GetDoubleField(int col);
        int             GetIntField(int col);
        sqlite3_int64   GetInt64Field(int col);
        const char*     GetTextField(int col);
        const void*     GetText16Field(int col);
        int             GetTypeField(int col);
        sqlite3_value*  GetFieldValue(int col);
        
        /*
         *  Purpose     Get length of a column(http://www.sqlite.org/c3ref/column_blob.html)
         */
        int				GetFieldBytes(int col);
        int				GetFieldBytes16(int col);
        
        /*
         *  Purpose     Bind parameter to SQL command(http://www.sqlite.org/c3ref/bind_blob.html)
         *	Remark		'size' parameter of BindText/BindText16 is the bytes (not the characters) of the data
         */
        int             BindBlob(int index, const void* data, int size, sqlite3_destructor_type destructor = SQLITE_STATIC);
        int             BindDouble(int index, double data);
        int             BindInt(int index, int data);
        int             BindInt64(int index, int64_t data);
        int             BindNull(int index);
        int             BindText(int index, const char* data, int size, sqlite3_destructor_type destructor = SQLITE_STATIC);
        int             BindText16(int index, const void* data, int size, sqlite3_destructor_type destructor = SQLITE_STATIC);
        int             BindValue(int index, const sqlite3_value* data);
        int             BindZeroBlob(int index, int size);
        
    private:
        
        bool            eof_;
        sqlite3_stmt*   stmt_;
    };
    
    /*
     *  Purpose     Auto transaction class
     *  Remark      The transaction will be update when the object destruct.
     */
    
    class SQLiteAutoTransaction
    {
    public:
        
        SQLiteAutoTransaction(SQLiteDB* db);
        virtual ~SQLiteAutoTransaction();
        
        bool Begin();
        bool Commit();
        bool Rollback();
        
    private:
        
        SQLiteDB* db_;
        bool      need_commit_;
    };
    
    
    /*
     *  Purpose     DB operation by sqlite3
     *  Remark      UTF-8 encoding
     */
    class SQLiteDB
    {
        friend class SQLiteStatement;
        
    public:
        
        enum OpenFlags
        {
            modeReadOnly      = SQLITE_OPEN_READONLY,       // Read only
            modeReadWrite     = SQLITE_OPEN_READWRITE,      // Read and write mode, it will failed when the file is not exist 
            modeCreate        = SQLITE_OPEN_CREATE,         // If the file not exist then create it. you can use it only with modeReadWrite
            modeMultiThread   = SQLITE_OPEN_NOMUTEX,        // No mutex mode, different thread can operate different db connection
            modeSerialized    = SQLITE_OPEN_FULLMUTEX,      // Mutex mode, different thread can operate one db connection
            //        modeSharedCache   = SQLITE_OPEN_SHAREDCACHE,    // Share cache
        };
        
        SQLiteDB();
        SQLiteDB(SQLiteDB& src);
        virtual ~SQLiteDB();
        
        SQLiteDB& operator=(SQLiteDB& src);
        
        /*
         *  Purpose     Open a database file
         *  flags       Open flag
         */
        bool Open(int flags = modeReadWrite|modeCreate|modeSerialized);
        
        /*
         *  Purpose     Open/Create an database file
         *  filename    Database file name
         *              ":memory:" means open a memory database
         *              NULL means open a temporarily database and it will be deleted when close it
         *  flags       Open flag
         */
        bool Open(const char* filename, int flags = modeReadWrite|modeCreate|modeSerialized,const std::string &key = "");
        
        /*
         *  Purpose     Close database
         */
        bool Close();
        
        /*
         *  Purpose     Compact database for memory fragment
         */
        bool Compact();
        
    public:
        
        bool IsValid() const;
        
        int GetLastErrorCode() const;
        int GetLastExtendedErrorCode() const;
        const char* GetLastErrorMessage() const;
        
        int GetChanges() const;
        int GetTotalChanges() const;
        sqlite3_int64 GetLastInsertRowId() const;
        
        /*
         *  Purpose     Execute the SQL command and prepare return result
         *  statement   Return result, you can call NextRow() to get real result
         *  sql_text    SQL command
         *  length      Length of SQL command.
         *  Remark      SQLite command£ºhttp://www.sqlite.org/lang.html
         *              Transaction is recommended.
         */
        int Query(SQLiteStatement& statement, const char* sql_text, int length = -1);
        
        /*
         *  Purpose     Execute the SQL command.
         *  sql_text    SQL command
         *  delegate    Result callback
         *  param       Custom parameter
         */
        int Query(const char* sql_text, SQLiteQueryDelegate delegate = NULL, void* param = NULL);
        
        /*
         *  Purpose     Execute the SQL command and put the result into result table.
         *  sql_text    SQL command
         *  table       Result table
         *  Remark      This function is low efficiency
         */
        int Query(const char* sql_text, SQLiteResultTable& table);
        
        /*
         *  Purpose     Interrupt all the operation
         */
        void Interrupt();
        
        /*
         *  Purpose     Set the waiting time that will return SQLITE_BUSY when the database is locked by a thread. 
         *  ms          Waiting time, the function will disable when ms is less then 0.
         */
        int SetBusyTimeout(int ms);
        
        /*
         *  Purpose     SQLite Version
         */
        static int GetVersion();
        
    private:
        
        mutable sqlite3*   sqlite3_;
    };
    
}  // namespace ndb

#endif