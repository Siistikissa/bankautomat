const db = require('../database');

const transactions = {
  getAll: function(callback) {
    return db.query('select * from transactions', callback);
  },
  getById: function(params, callback) {
    return db.query('select * from (select * from transactions where ac_id = ? order by comment_id desc limit ?,?) t1 order by date', 
    [params.id,params.start,params.stop], callback);
  },
  add: function(transactions, callback) {
    return db.query(
      'select * from (select * from transactions where ac_id=? order by tr_id desc limit ?,?) t1 order by tr_date', 
      [transactions.id, transactions.start, transactions.stop], 
      callback
    );
  },
  withdraw: function(transactions, callback) {
    if(transactions.type == 'balance'){
      return db.query(
        'update accounts set balance=? where cu_id=?', 
        [transactions.newAmount, transactions.cu_id], 
        callback
      );
    }
    else if(transactions.type == 'credit'){
      return db.query(
        'update accounts set credit=? where cu_id=?', 
        [transactions.newAmount, transactions.cu_id], 
        callback
      );
    }
  },
  insertTransaction: function(transactions, callback) {
    return db.query(
      'insert into transactions(transaction,ac_id,tr_date) values(?,?,NOW())', 
      [transactions.transaction, transactions.ac_id], 
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