const db = require('../database');

const transactions = {
  getAll: function(callback) {
    return db.query('select * from transactions', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from transactions where tr_id=?', [id], callback);
  },
  add: function(transactions, callback) {
    return db.query(
      'insert into transactions (transaction,ac_id,tr_date) values(?,?,?)',
      [transactions.transaction, transactions.ac_id, transactions.tr_date],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transactions where tr_id=?', [id], callback);
  },
  update: function(id, transactions, callback) {
    return db.query(
      'update transactions set transaction=?,ac_id=?, tr_date=? where tr_id=?',
      [transactions.transaction, transactions.ac_id, transactions.tr_date, id],
      callback
    );
  }
};
module.exports = transactions;