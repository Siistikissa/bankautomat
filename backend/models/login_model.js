const db = require('../database');

const login = {
    checkPassword: function(serial, callback) {
      console.log(serial);
        return db.query(
          'select pin from cards where serial = ?', [serial],
          callback
        ) 
        }
    };
module.exports = login;