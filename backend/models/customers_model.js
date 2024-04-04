const db = require('../database');

const customers = {
  getAll: function(callback) {
    return db.query('select * from customers', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from customers where cu_id=?', [id], callback);
  },
  add: function(customers, callback) {
    return db.query(
      'insert into customers (fname,lname) values(?,?)',
      [customers.fname, customers.lname],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customers where cu_id=?', [id], callback);
  },
  update: function(id, customers, callback) {
    return db.query(
      'update customers set fname=?,lname=? where cu_id=?',
      [customers.fname, customers.lname, id],
      callback
    );
  }
};
module.exports = customers;