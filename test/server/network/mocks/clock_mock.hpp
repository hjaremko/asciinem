#ifndef ASCIINEM_CLOCK_MOCK_HPP
#define ASCIINEM_CLOCK_MOCK_HPP

#include "network/interfaces/subject.hpp"

#include "gmock/gmock.h"

class clock_mock : public asciinem::server::network::subject
{
public:
    MOCK_METHOD( void,
                 attach,
                 ( const asciinem::server::network::observer::pointer& ),
                 ( override ) );
    MOCK_METHOD( void,
                 detach,
                 ( const asciinem::server::network::observer::pointer& ),
                 ( override ) );
    MOCK_METHOD( void, notify, (), ( override ) );
};

#endif // ASCIINEM_CLOCK_MOCK_HPP
