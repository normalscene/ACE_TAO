#include "Policy_Verifier.h"

ACE_RCSID (tao, Policy_Verifier, "$Id$")


Policy_Verifier::Policy_Verifier (void)
{
  ACE_OS_String::strcpy (this->base_object_ref_,
                         "file://");
  ACE_OS_String::strcpy (this->overridden_object_ref_,
                         "file://");
}

Policy_Verifier::~Policy_Verifier (void)
{
  // No Op.
}

void
Policy_Verifier::init (int argc,
                       char *argv[],
                       CORBA::Environment &ACE_TRY_ENV)
{
  ACE_TRY
    {
      this->orb_ =
        CORBA::ORB_init (argc, argv, "", ACE_TRY_ENV);
      ACE_TRY_CHECK;

      ACE_Arg_Shifter arg_shifter (argc, argv);

      while (arg_shifter.is_anything_left ())
        {
          char *arg;
          // IOR File Name Option.
          if ((arg = arg_shifter.get_the_parameter ("-POAConfigFile")))
            {
              this->rt_poa_properties_ =
                RT_Properties::read_from (arg, ACE_TRY_ENV);
              ACE_TRY_CHECK;

              ACE_OS_String::strcat (this->base_object_ref_,
                                     this->rt_poa_properties_->ior_source ());
            }
          else if ((arg = arg_shifter.get_the_parameter ("-ObjectConfigFile")))
            {
              this->rt_object_properties_ =
                RT_Properties::read_from (arg, ACE_TRY_ENV);
              ACE_TRY_CHECK;

              ACE_OS_String::strcat (this->overridden_object_ref_,
                                     this->rt_object_properties_->ior_source ());

            }
          else
            arg_shifter.consume_arg ();

        }

      if ((this->rt_poa_properties_ == 0) || (this->rt_object_properties_ == 0))
        {
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("Configuration file missing!\n")));
          return;
        }

      // Get the Object references.
      CORBA::Object_var object = this->orb_->string_to_object (this->base_object_ref_,
                                                               ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (!Policy_Tester::check_reference (object.in (), "Invalid IOR file!\n"))
        return;

      this->base_object_ = Counter::_narrow (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (!Policy_Tester::check_reference (this->base_object_,
                                           "Unable to convert the IOR to the proper object reference.\n"))
        return;

      object = this->orb_->string_to_object (this->overridden_object_ref_, ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (!Policy_Tester::check_reference (object.in (), "Invalid IOR file!\n"))
        return;

      this->overridden_object_ = Counter::_narrow (object.in (), ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (!Policy_Tester::check_reference (this->overridden_object_,
                                           "Unable to convert the IOR to the proper object reference.\n"))
        return;

    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "CORBA Excaption Raised");
    }
  ACE_ENDTRY;
}

void
Policy_Verifier::run (CORBA::Environment &ACE_TRY_ENV )
{
  this->verify_reference (this->base_object_,
                          this->rt_poa_properties_,
                          ACE_TRY_ENV);
  ACE_CHECK;

  this->verify_reference (this->overridden_object_,
                          this->rt_object_properties_,
                          ACE_TRY_ENV);
  ACE_CHECK;
}

void
Policy_Verifier::verify_reference (Counter_ptr object,
                                   RT_Properties *rt_properties,
                                   CORBA::Environment &ACE_TRY_ENV)
{

  ACE_TRY
    {
      CORBA::Policy_var policy_ptr =
        object->_get_policy (RTCORBA::PRIORITY_MODEL_POLICY_TYPE,
                             ACE_TRY_ENV);
      ACE_TRY_CHECK;

      if (Policy_Tester::check_reference (policy_ptr, "Unable to get Priority Policy.\n"))
        {
          RTCORBA::PriorityModelPolicy_var priority_policy =
            RTCORBA::PriorityModelPolicy::_narrow (policy_ptr);

          RTCORBA::PriorityModel priority_model =
            priority_policy->priority_model (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          RTCORBA::Priority priority =
            priority_policy->server_priority (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          if (priority_model == RTCORBA::SERVER_DECLARED)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_TEXT ("\n\nPriority Model: RTCORBA::SERVER_DECLARED\n")
                        ));

          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("Priority Model: %d\nCORBA Priority: %d\n\n"),
                      priority_model,
                      priority
                      ));


          if (priority != rt_properties->priority ())
            ACE_DEBUG ((LM_DEBUG,
                        ACE_TEXT ("Priority Value Mismatch.\n")));
        }

      policy_ptr = object->_get_policy (RTCORBA::PRIORITY_BANDED_CONNECTION_POLICY_TYPE,
                                        ACE_TRY_ENV);
      if (Policy_Tester::check_reference (policy_ptr,
                                          "Unable to get Priority Banded Policy\n"))
        {

          RTCORBA::PriorityBandedConnectionPolicy_var priority_banded_policy =
            RTCORBA::PriorityBandedConnectionPolicy::_narrow (policy_ptr,
                                                              ACE_TRY_ENV);
          ACE_TRY_CHECK;


          if (Policy_Tester::check_reference (priority_banded_policy,
                                              "Unable to get Priority Banded Policy\n"))
            {

              // Here we have a priority banded connection policy.

              RTCORBA::PriorityBands_var pb =
                priority_banded_policy->priority_bands ();
              unsigned int band_num = pb->length ();
              if (band_num != rt_properties->priority_bands ().length ())
                ACE_DEBUG ((LM_DEBUG,
                            ACE_TEXT ("Mismatching Number of Priority Bands!\n")));

              for (unsigned int i = 0; i < band_num; ++i)
                {
                  ACE_DEBUG ((LM_DEBUG,
                              ACE_TEXT ("Priority Band <%d>: (%d, %d)\n"),
                              i,
                              pb[i].low,
                              pb[i].high
                              ));


                  if ((band_num == rt_properties->priority_bands ().length ()) &&
                      ((pb[i].low !=  rt_properties->priority_bands ()[i].low) ||
                       (pb[i].high !=  rt_properties->priority_bands ()[i].high)))
                    ACE_DEBUG ((LM_DEBUG,
                                ACE_TEXT ("Mismatching Priority Band Range!\n")));

                }
            }
        }
      policy_ptr = object->_get_policy (RTCORBA::CLIENT_PROTOCOL_POLICY_TYPE,
                                        ACE_TRY_ENV);
      if (Policy_Tester::check_reference (policy_ptr, "Unable to get Client Protocol Policy\n"))
        {
          RTCORBA::ClientProtocolPolicy_var client_protocol_policy =
            RTCORBA::ClientProtocolPolicy::_narrow (policy_ptr, ACE_TRY_ENV);
          ACE_TRY_CHECK;

          RTCORBA::ProtocolList_var protocol_list =
            client_protocol_policy->protocols (ACE_TRY_ENV);
          ACE_TRY_CHECK;

          for (unsigned int  i = 0; i < protocol_list->length (); i++)
            ACE_DEBUG ((LM_DEBUG,
                        ACE_TEXT ("\nThe Client Protocol Type: %d\n"),
                        protocol_list[i].protocol_type));

        }

    }
  ACE_CATCHANY
    {
      ACE_PRINT_EXCEPTION (ACE_ANY_EXCEPTION, "CORBA Exception Raised");
    }

  ACE_ENDTRY;
}
