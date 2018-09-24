let ButtonHandler = {
	bhChannel: null,

	init(socket){

		socket.connect();
		this.onReady(socket);
	},

	onReady(socket){
		this.bhChannel = socket.channel("led-channel");

		this.bhChannel.on("render_leds", (resp) => {
			this.renderLEDS(resp)
		});

		this.bhChannel.join()
			.receive("ok", (list) => {
				this.renderLEDS(list)
			})
			.receive("error", resp => console.log("Join failed") )

		for(let i = 1; i <= 25; i++){
			let button = this.getButtonElement(i);

			this.setButtonStatus(button);

			button.addEventListener("click", e => {
				this.bhChannel.push(button.id)
					.receive("error", e => console.log(e) )
			})
		}
	},

	renderLEDS({list}){
		console.log("Setting:", list);
		list.forEach(function(status, index){
			let button = ButtonHandler.getButtonElement(index + 1);
			ButtonHandler.setButtonStatus(button, status);
		})
	},

	getButtonElement(buttonNumber){
		let ledButtonId = `${buttonNumber}`.padStart(2, "0");
		let ledButton = document.getElementById(`led-btn-${ledButtonId}`);
		return ledButton;
	},

	setButtonStatus(ledButton, buttonOn){
		if(buttonOn){
			ledButton.classList = "led-btn led-btn-on";
		}
		else{
			ledButton.classList = "led-btn led-btn-off";
		}
	}
}

export default ButtonHandler
