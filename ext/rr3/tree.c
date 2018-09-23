#include <r3/r3.h>
#include "tree.h"

extern VALUE rb_mRr3;
VALUE rb_cTree;

void init_tree(){
  rb_cTree = rb_define_class_under(rb_mRr3, "Tree", rb_cObject);
  rb_define_method(rb_cTree, "initialize", rb_tree_initialize, 1);
  rb_define_method(rb_cTree, "insert", rb_tree_insert, 2);
  rb_define_method(rb_cTree, "compile!", rb_tree_compile, 0);
  rb_define_method(rb_cTree, "match", rb_tree_match, 2);
  rb_define_method(rb_cTree, "dump", rb_tree_dump, 1);
}

static VALUE rb_tree_initialize(VALUE self, VALUE size){
  node *n = r3_tree_create(FIX2INT(size));
  rb_ivar_set(self, rb_intern("@root"), Data_Wrap_Struct(rb_cObject, NULL, release, n));
  return self;
}

static VALUE rb_tree_insert(VALUE self, VALUE methods, VALUE path){
  r3_tree_insert_routel(root(self), NUM2INT(methods), RSTRING_PTR(path), RSTRING_LEN(path), data);
  return Qnil;
}

static VALUE rb_tree_compile(VALUE self){
  char *errstr = NULL;
  if(r3_tree_compile(root(self), &errstr) != 0){
    rb_raise(rb_eRuntimeError, "%s", errstr);
    free(errstr);
  }
  return Qnil;
}

static VALUE rb_tree_match(VALUE self, VALUE methods, VALUE path){
  match_entry *entry = match_entry_create(RSTRING_PTR(path), RSTRING_LEN(path));
  entry->request_method = NUM2INT(methods);

  R3Route *matched_node = r3_tree_match_route(root(self), entry);

  match_entry_free(entry);

  return matched_node ? *((VALUE*) matched_node->data) : Qfalse;
}

static VALUE rb_tree_dump(VALUE self, VALUE level){
  r3_tree_dump(root(self), FIX2INT(level));
  return Qnil;
}

static void release(node *n){
  r3_tree_free(n);
}

inline static node* root(VALUE self){
  node *root;
  Data_Get_Struct(rb_ivar_get(self, rb_intern("@root")), node, root);
  return root;
}