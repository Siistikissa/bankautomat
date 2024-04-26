const db = require('../database');

const accounts = {
  getAll: function(callback) {
    return db.query('select * from accounts', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from accounts where ac_id=?', [id], callback);
  },
  add: function(accounts, callback) {
    return db.query(
      'select * from accounts where cu_id = ?',
      [accounts.cu_id],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from accounts where ac_id=?', [id], callback);
  },
  update: function(id, accounts, callback) {
    return db.query(
      'update accounts set balance=?,credit=?, cu_id=?, ca_id=? where ac_id=?',
      [accounts.balance, accounts.credit, accounts.cu_id,accounts.ca_id, id],
      callback
    );
  }
};
module.exports = accounts;