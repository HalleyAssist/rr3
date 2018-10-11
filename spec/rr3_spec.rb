require 'spec_helper'

describe Rr3 do
  before(:all)do
    @tree = Rr3::Tree.new(10)
    @tree.insert 1, "/bar", 4
    @tree.insert 1, "/zoo", 3
    @tree.insert 1, "/foo/bar", 1
    @tree.insert 1, "/post/{id}", 2
    @tree.insert 1, "/user/{id:\\d+}", 5
    @tree.compile!
  end

  it 'matches' do
    expect(@tree.match(1, "/bar")["data"]).to eql 4
    expect(@tree.match(1, "/zoo")["data"]).to eql 3
    expect(@tree.match(1, "/foo/bar")["data"]).to eql 1
    expect(@tree.match(1, "/post/1234")["slugs"][0]).to eql "1234"
    expect(@tree.match(1, "/user/1234")["slugs"][0]).to eql "1234"
    expect(@tree.match(1, "/user/xxx")).to eql false
    expect(@tree.match(1, "/asd")).to eql false
  end

  it 'dumps' do
    expect{ @tree.dump(0) }.not_to raise_error
  end
end
