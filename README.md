# Creating a device in Google IOT Core
openssl ecparam -genkey -name prime256v1 -noout -out ec_private.pem
openssl ec -in ec_private.pem -pubout -out ec_public.pem

gcloud iot devices create device-001 --region=europe-west1 --registry=sensors --public-key path=ec_public.pem,type=es256
