# Rr3

## Dependency

### OS X

    brew install r3

### Ubuntu PPA

The PPA for libr3 can be found in https://launchpad.net/~r3-team/+archive/libr3-daily

## Installation

    $ gem install rr3

## Usage

```ruby
require 'rr3'
@tree = Rr3::Tree.new(10)
@tree.insert "/bar"
@tree.insert "/zoo", 9527
@tree.insert "/foo/bar", 9527
@tree.insert "/post/{id}", 9527
@tree.insert "/user/{id:\\d+}", 9527
@tree.compile!
@tree.match "/user/xxx"  # => false # not matched
@tree.match "/asd"       # => false
@tree.match "/bar"       # => nil   # matched, and the route data is `nil`
@tree.match "/zoo"       # => 9527  # matched, and the route data is `9527`
@tree.match "/foo/bar"   # => 9527
@tree.match "/post/1234" # => 9527
@tree.match "/user/1234" # => 9527
```