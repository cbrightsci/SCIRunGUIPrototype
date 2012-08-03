/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#ifndef ENGINE_SCHEDULER_SCHEDULER_INTERFACES_H
#define ENGINE_SCHEDULER_SCHEDULER_INTERFACES_H

#include <Core/Dataflow/Network/NetworkFwd.h>
#include <list>
#include <stdexcept>
#include <Engine/Scheduler/Share.h>

namespace SCIRun {
namespace Engine {

  //Serial
  class SCISHARE ModuleExecutionOrder
  {
  public:
    typedef std::list<std::string> ModuleIdList;
    typedef ModuleIdList::iterator iterator;
    typedef ModuleIdList::const_iterator const_iterator;

    explicit ModuleExecutionOrder(const ModuleIdList& list);
    const_iterator begin() const;
    const_iterator end() const;
  private:
    ModuleIdList list_;
  };

  class NetworkHasCyclesException : public std::invalid_argument
  {
  public:
    explicit NetworkHasCyclesException(const char* str);
  };

  //Serial
  class SCISHARE Scheduler
  {
  public:
    virtual ~Scheduler();
    virtual ModuleExecutionOrder schedule(const SCIRun::Domain::Networks::NetworkInterface& network) = 0;
  };

  //TODO: types for ParallelScheduler, etc

  class SCISHARE NetworkExecutor
  {
  public:
    virtual ~NetworkExecutor();
    virtual void executeAll(const SCIRun::Domain::Networks::ExecutableLookup& lookup, ModuleExecutionOrder order) = 0;
    //TODO
    // virtual void connectNetworkFinishedListener()...
  };

}
}

#endif