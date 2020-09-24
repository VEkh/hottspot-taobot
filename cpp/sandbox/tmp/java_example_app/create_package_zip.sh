echo "Cleaning the existing repo and zip files"
rm -rf java_example_app
rm -rf sample-client
rm  -f java_example_app.zip
echo "Cloning the repo"
echo "Enter bitbucket username"
read user
git clone https://$user@bitbucket.etrade.com/scm/api/sample-client.git -b integration java_example_app
echo "Removing unnecessary files under the repo"
rm -rf  java_example_app/EtradePythonClient
rm -rf  java_example_app/README.md
rm -rf  java_example_app/.git
echo "Starting the zip process"
cd java_example_app
mv example-app-java java_example_app
rm -rf java_example_app/.git
zip -r java_example_app.zip java_example_app
echo "java_example_app.zip created...."
echo "Cleaing up the temporary files"
rm -rf ../zip
mkdir ../zip
cp java_example_app.zip ../zip
cd ..
rm -rf java_example_app
