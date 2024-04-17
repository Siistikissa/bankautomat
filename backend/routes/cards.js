var express = require('express');
var router = express.Router();
const cards = require('../models/cards_model');
const bcrypt = require('bcryptjs');
const saltRounds = 10;

router.get('/',
    function (request, response) {
        cards.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:id',
    function (request, response) {
        cards.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/', 
function(request, response) {
  cards.searchCard(request.body.serial, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      console.log(dbResult);
      response.json(dbResult);
    }
  });
});


router.delete('/:id', 
function(request, response) {
  cards.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  
  bcrypt.genSalt(saltRounds, (err, salt) => {
    if (err) {
        // Handle error
        return;
    }
    
    // Salt generation successful, proceed to hash the password
    bcrypt.hash(request.body.pin, salt, (err, hash) => {
      if (err) {
          // Handle error
          return;
      }
  
  // Hashing successful, 'hash' contains the hashed password
  console.log('Hashed password:', hash);
  request.body.pin = hash;
  cards.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
    });
  });
});

module.exports = router;
