require 'rr3'

tree = Rr3::Tree.new(10)
tree.insert(1, "/test/{id}", 123)
tree.compile!

result = tree.match 1, "/test/123"
puts(result)
