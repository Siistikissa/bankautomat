const db = require('../database');

const cards = {
  getAll: function(callback) {
    return db.query('select * from cards', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from cards where ca_id=?', [id], callback);
  },
  add: function(cards, callback) {
    return db.query(
      'insert into cards (pin,cu_id,serial) values(?,?,?)',
      [cards.pin, cards.cu_id, cards.serial],
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