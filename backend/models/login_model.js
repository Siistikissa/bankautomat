const db = require('../database');

const login = {
    checkPassword: function(username, callback) {
        return db.query(
          'select pin from cards where serial = ?', [username],
          callback
        )
        }
    };
module.exports = login;