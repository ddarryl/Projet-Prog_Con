#!/bin/bash

# Define database credentials
DB_USER="phpmyadmin"
DB_PASS="Ruymustang_97"
DB_NAME="RestaurantManagement"

# Drop and recreate the database
mysql -u $DB_USER -p$DB_PASS -e "DROP DATABASE IF EXISTS $DB_NAME; CREATE DATABASE $DB_NAME;"

# Run the creation script
mysql -u $DB_USER -p$DB_PASS $DB_NAME < Script.sql

echo "Database $DB_NAME has been reset and populated with test data."
