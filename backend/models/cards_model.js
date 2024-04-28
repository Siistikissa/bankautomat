const db = require('../database');

const cards = {
  getAll: function(callback) {
    return db.query('select * from cards', callback);
  },
  searchAcc: function(cu_id,callback){
    return db.query('select * from accounts where cu_id=?', [cu_id], callback);
  },
  getById: function(id, callback) {
    return db.query('select * from cards where ca_id=?', [id], callback);
  },
  searchCard: function(cards, callback) {
    return db.query(
      'select cu_id from cards where serial = ?',
      [cards],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from cards where ca_id=?', [id], callback);
  },
  update: function(id, cards, callback) {
    return db.query(
      'update cards set pin=?,cu_id=?, serial=? where ca_id=?',
      [cards.pin, cards.cu_id, cards.serial, id],
      callback
    );
  }
};
module.exports = cards;