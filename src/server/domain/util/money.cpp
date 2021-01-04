#include "server/domain/util/money.hpp"

#include <cmath>
namespace asciinem::server::domain
{

money::money() = default;

money::money( double d ) : m_money_( static_cast<int>( d * SCALE() ) )
{
    FIX();
}

money::money( const money& m ) = default;

auto money::operator=( const money& m ) -> money& = default;
auto money::operator=( double d ) -> money&
{
    m_money_ = static_cast<int>( d * SCALE() );
    FIX();
    return *this;
}

money::operator double() const
{
    return m_money_ / SCALE();
}

money::operator int() const
{
    return static_cast<int>(m_money_);
}

void money::FIX()
{
    m_money_ =
        ( m_money_ > 0.0 ? floor( m_money_) : ceil( m_money_) );
}

auto money::operator+=( const money& m ) -> money&
{
    m_money_ += m.m_money_;
    return *this;
}

auto money::operator-=( const money& m ) -> money&
{
    m_money_ -= m.m_money_;
    return *this;
}

auto money::operator*=( double d ) -> money&
{
    m_money_ = static_cast<int>( m_money_ * d );
    FIX();
    return *this;
}

auto money::operator/=( double d ) -> money&
{
    m_money_ = static_cast<int>( m_money_ / d );
    FIX();
    return *this;
}

auto operator+( const money& m, const money& mm ) -> money
{
    money temp;
    temp.m_money_ = m.m_money_ + mm.m_money_;
    return temp;
}

auto operator-( const money& m, const money& mm ) -> money
{
    money temp;
    temp.m_money_ = m.m_money_ - mm.m_money_;
    return temp;
}

auto operator*( const money& m, double d ) -> money
{
    money temp;
    temp.m_money_ = static_cast<int>( m.m_money_ * d );
    temp.FIX();
    return temp;
}
auto operator*( double d, const money& m ) -> money
{
    return ( m * d );
}

auto operator/( const money& m, const money& mm ) -> double
{
    return m.m_money_ / mm.m_money_;
}

auto operator==( const money& m, const money& mm ) -> bool
{
    return m.m_money_ == mm.m_money_;
}

auto operator<( const money& m, const money& mm ) -> bool
{
    return m.m_money_ < mm.m_money_;
}

} // namespace asciinem::server::domain
