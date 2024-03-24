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
      'insert into cards (pin,cu_id,key) values(?,?,?)',
      [cards.pin, cards.cu_id, cards.key],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from cards where ca_id=?', [id], callback);
  },
  update: function(id, cards, callback) {
    return db.query(
      'update cards set pin=?,cu_id=?, key=? where ca_id=?',
      [cards.pin, cards.cu_id, cards.key, id],
      callback
    );
  }
};
module.exports = cards;