#ifndef _ILRD_RD734_FDLISTENER_HPP_
#define _ILRD_RD734_FDLISTENER_HPP_

#include <vector>
#include <boost/chrono.hpp>
#include <boost/function.hpp>

#include "reactor_typedefs.hpp"

namespace ilrd
{

class FDListener
{
public:
    enum Mode {READ, WRITE, EXCEPT};
    
    typedef std::pair<int, Mode> ModeAndFD;
    typedef std::vector<ModeAndFD> FDVector;
    
    static FDVector Wait(FDVector& fds_);

private:
    const static boost::chrono::milliseconds s_timeout;
};

//move to cpp
const boost::chrono::milliseconds FDListener::s_timeout(2000);

} // namespace ilrd

#endif // _ILRD_RD734_FDLISTENER_HPP_