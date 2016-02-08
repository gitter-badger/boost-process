// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/child.hpp
 *
 * Defines a child process class.
 */

#ifndef BOOST_PROCESS_CHILD_HPP
#define BOOST_PROCESS_CHILD_HPP

#include <boost/process/config.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/posix/child.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/windows/child.hpp>
#endif

namespace boost { namespace process {

#if defined(BOOST_POSIX_API)
namespace api = ::boost::process::posix;
#elif defined(BOOST_WINDOWS_API)
namespace api = ::boost::process::windows;
#else
#error "boost.process only works with "
#endif


/**
 * Represents a child process.
 *
 * On Windows child is movable but non-copyable. The destructor
 * automatically closes handles to the child process.
 */
class child
{
    api::child_handle _child_handle;
    int _exit_code = -1;
    bool _attached = true;
public:
    typedef api::child_handle::process_handle_t native_handle_t;
    explicit child(api::child_handle &&ch) : _child_handle(ch) {}

    child(const child&) = delete;
    child(child && ) = default;

    child& operator=(const child&) = delete;
    child& operator=(child && ) = default;

    native_handle_t native_handle() const { return _child_handle.process_handle(); }


    int exit_code() const;
    int get_pid() const;

    bool running();

    void terminate();

    void wait();

    template< class Rep, class Period >
    bool wait_for  (const std::chrono::duration<Rep, Period>& rel_time);

    template< class Clock, class Duration >
    bool wait_until(const std::chrono::time_point<Clock, Duration>& timeout_time );

    void detach();
    void attach();

};

}}
#endif
