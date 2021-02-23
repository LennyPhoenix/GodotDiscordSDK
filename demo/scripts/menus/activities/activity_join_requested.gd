extends PanelContainer


onready var user_info: = $VBoxContainer/UserInfo


func _ready() -> void:
	DiscordManager.activities.connect(
		"activity_join_request",
		self, "_on_activity_join_request"
	)


func _on_activity_join_request(user: Discord.User) -> void:
	user_info.user = user
