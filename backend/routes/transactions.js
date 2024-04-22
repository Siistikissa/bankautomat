var express = require('express');
var router = express.Router();
const transactions = require('../models/transactions_model');

router.get('/',
    function (request, response) {
        transactions.getAll(request.params, function (err, dbResult) {
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
        transactions.getById(request.params, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/', 
function(request, response) {
  //console.log("body : " + request.body)
  transactions.add(request.body, function(err, dbResult) {
    if (err) {
      console.log("transaction post error : "+ err)
      response.json(err);
    } else {
      console.log("result : " + dbResult);
      response.json(dbResult);
    }
  });
});

router.post('/withdraw', 
function(request, response) {
  transactions.withdraw(request.body, function(err, dbResult) {
    if (err) {
      console.log("withdarw post error : "+ err);
      response.json(err);
    } else {
      transactions.insertTransaction(request.body, function(errInner, dbResultInner){
        if(errInner){
          console.log("transactionInsert post error : "+ errInner)
          response.json(err);
        }
        else{
          console.log("result : " + dbResultInner);
          response.json(dbResult)
        }
      });
    }
  });
});

router.delete('/:id', 
function(request, response) {
  transactions.delete(request.params.id, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});


router.put('/:id', 
function(request, response) {
  transactions.update(request.params.id, request.body, function(err, dbResult) {
    if (err) {
      response.json(err);
    } else {
      response.json(dbResult);
    }
  });
});

module.exports = router;
