/*
 * Copyright (c) 2011, Intel Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _GETLOGPAGE_H_
#define _GETLOGPAGE_H_

#include "cmd.h"
#include "getLogPageDefs.h"


class GetLogPage;    // forward definition
typedef boost::shared_ptr<GetLogPage>               SharedGetLogPagePtr;
typedef boost::shared_ptr<const GetLogPage>         ConstSharedGetLogPagePtr;
#define CAST_TO_GETLOGPAGE(shared_trackable_ptr)    \
        boost::shared_polymorphic_downcast<GetLogPage>(shared_trackable_ptr);


/**
* This class implements the GetLogPage admin cmd
*
* @note This class may throw exceptions.
*/
class GetLogPage : public Cmd
{
public:
    GetLogPage();
    virtual ~GetLogPage();

    /// Used to compare for NULL pointers being returned by allocations
    static SharedGetLogPagePtr NullGetLogPagePtr;
    static const uint8_t Opcode;
    /// size of a single log entry only, may request multiple entry's from DUT
    static const uint16_t ERRINFO_DATA_SIZE;
    static const uint16_t SMART_DATA_SIZE;
    static const uint16_t FIRMSLOT_DATA_SIZE;

    /**
     * Set the number of DWORDs to return from the DUT
     * @param numDW Pass the number of DWORDs
     */
    void SetNUMD(uint16_t numDW);
    uint16_t GetNUMD() const;

    typedef enum LogID {
        LOGID_ERROR_INFO   = 0x01,
        LOGID_SMART_HEALTH = 0x02,
        LOGID_FW_SLOT      = 0x03
    } LogID;

    /**
     * Set the log identifier
     * @param logID Pass the log ID to set
     */
    void SetLID(uint16_t logID);
    uint16_t GetLID() const;

    /**
     * Append the entire contents of this cmds' contents, any PRP payload,
     * and any meta data it may contain to the named file.
     * @param filename Pass the filename as generated by macro
     *      FileSystem::PrepDumpFile().
     * @param fileHdr Pass a custom file header description to dump
     */
    virtual void Dump(DumpFilename filename, string fileHdr) const;


private:
    /// Details the fields within the get log page error log
    static GetLogPageDataType mErrLogMetrics[];
    /// Details the fields within the get log page smart/health log
    static GetLogPageDataType mSmartLogMetrics[];
    /// Details the fields within the get log page FW slot log
    static GetLogPageDataType mFwLogMetrics[];

    /// General functions to support the more specific public versions
    void Dump(FILE *fp, int field, GetLogPageDataType *idData) const;
};


#endif
