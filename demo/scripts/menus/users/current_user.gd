extends PanelContainer


onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/Result/LineEdit
onready var premium_type_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/PremiumType/LineEdit
onready var user_flags_button: = $VBoxContainer/MarginContainer/VBoxContainer/Flags/OptionButton
onready var user_flags_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/Flags/LineEdit
onready var user_info: = $VBoxContainer/MarginContainer/VBoxContainer/User


func _ready() -> void:
	for item in Discord.UserFlag.keys():
		user_flags_button.add_item(item, Discord.UserFlag[item])

	var _err: = user_flags_button.connect(
		"item_selected",
		self, "_on_flags_item_selected"
	)

	_err = DiscordManager.users.connect(
		"current_user_update",
		self, "_on_current_user_update"
	)


func _on_current_user_update() -> void:
	_on_flags_item_selected(0)

	DiscordManager.users.get_current_user()
	var ret: Array = yield(DiscordManager.users, "get_current_user_callback")
	var result: int = ret[0]
	var user: Discord.User = ret[1]

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)
	user_info.user = user

	DiscordManager.users.get_current_user_premium_type()
	ret = yield(DiscordManager.users, "get_current_user_premium_type_callback")
	result = ret[0]
	var premium_type: int = ret[1]

	if result == Discord.Result.OK:
		premium_type_line_edit.text = DiscordManager.enum_to_string(
			Discord.PremiumType,
			premium_type
		)


func _on_flags_item_selected(index: int) -> void:
	var id: int = user_flags_button.get_item_id(index)

	DiscordManager.users.current_user_has_flag(id)
	var ret: Array = yield(DiscordManager.users, "current_user_has_flag_callback")
	var result: int = ret[0]
	var has_flag: bool = ret[1]

	if result == Discord.Result.OK:
		user_flags_line_edit.text = str(has_flag)
