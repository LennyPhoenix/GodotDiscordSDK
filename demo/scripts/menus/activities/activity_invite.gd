extends PanelContainer


onready var type_options: = $VBoxContainer/Type/OptionButton
onready var user_info: = $VBoxContainer/UserInfo
onready var activity_info: = $VBoxContainer/Activity


func _ready() -> void:
	for item in Discord.ActivityActionType.keys():
		type_options.add_item(item, Discord.ActivityActionType[item])

	DiscordManager.activities.connect(
		"activity_invite",
		self, "_on_activity_invite"
	)


func _on_activity_invite(type: int, user: Discord.User, activity: Discord.Activity) -> void:
	var index: int = type_options.get_item_index(type)
	type_options.select(index)

	user_info.user = user
	activity_info.activity = activity
