
client_handler(address_of_pipeline) {
	// this is a thread to handle the connection of a client
	// the write channel and read channel is open
	while (thread_status == ON) {
		// wait for a upcomming message 
		message = read(pipeline)
		// if the message is not equal to "exit" then continue
		// but if it is then thread_status = OFF; and break;
		
		// we have a interthread variable to 

		
	}
}

main() {

	while(serverState == true) {
		//if have incomming byte in pipeline 
		request = read() // blocking here until have byte
		// then check if this is a request to connect
		// if it is a request to connect and client-counter is lower than max then accept the connection
		if (request == CONNECT) {
			// create a new named pipeline and send pipeline's address back to the client
			address_of_pipeline = create_pipe()
			// create a new thread and pass the just created pipeline to the thread
			pthread_new(address_of_pipeline)
		}
		// if it not a request to connect then clear the request


	}


}
